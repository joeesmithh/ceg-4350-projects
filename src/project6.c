#include "project6.h"

#if PROJECT == 6
int kernel()
{
    startkernel(startshell);
    return 0;
}
#endif

int deleteFile()
{
    // i. Check to see if currentFile is opened, if not return with error code (i.e. return -1)
    // ----------------------------------------------------------------------------------------------------------------------------------
    if (!currentFile.isOpened)
    {
        print("Error: cannot delete a file that is not open!\n");
        return -1;
    }

    // ii. Overwrite all FAT clusters in the FAT table for this file with x0000
    // ----------------------------------------------------------------------------------------------------------------------------------
    uint16 cluster = currentFile.directoryEntry->startingCluster; // Start at file's first cluster
    while (cluster != 0xFFFF)
    {
        uint16 next = fat0->clusters[cluster]; // Get next cluster before zeroing
        fat0->clusters[cluster] = 0x0000;      // Overwrite fat0 with 0
        fat1->clusters[cluster] = 0x0000;      // Overwrite fat1 with 0
        cluster = next;                        // Set next cluster
    }

    // iii. Remove the directory entry that has the currentFile.directoryEntry->filename inside
    //      of it at currentDirectory.startingAddress by overwriting the first element with NULL (x00)
    //      or by overwriting entire directory entry with NULL
    // ----------------------------------------------------------------------------------------------------------------------------------
    directory_entry_t *deleteEntry = currentFile.directoryEntry; // Pointer to the 32-byte entry we want to erase
    uint8 emptyEntry[32] = {0};                                  // 32-byte zeroed buffer
    *deleteEntry = *(directory_entry_t *)emptyEntry;             // Overwrite the entry in memory with zeroed buffer

    // 1. Recommended: overwrite this directory entry with the last directory entry in the directory
    // ----------------------------------------------------------------------------------------------------------------------------------
    uint32 maxEntries = currentDirectory.directoryEntry->fileSize / 32;              // Total possible entries = dir size / 32
    directory_entry_t *base = (directory_entry_t *)currentDirectory.startingAddress; // Base pointer to the array of directory entries
    directory_entry_t *lastEntry = 0;                                                // Will track the last entry that is not null

    // Find last entry by checking if the first byte of the base directory is not null, then update lastEntry
    for (uint32 i = 0; i < maxEntries; i++)
        if (base[i].filename[0] != 0)
            lastEntry = &base[i];

    // Replace deleteEntry with lastEntry when lastEntry unique and not null, then zero lastEntry
    if (lastEntry != 0 && lastEntry != deleteEntry)
    {
        *deleteEntry = *lastEntry;
        *lastEntry = *(directory_entry_t *)emptyEntry;
    }

    // iv. Call writeFATs() to write the changes made to the FATs back to the disk
    // ----------------------------------------------------------------------------------------------------------------------------------
    if (writeFATs())
    {
        // 1. If error occurs, return non zero
        print("Error: writeFATs has failed!\n");
        return -2;
    }

    // v. Call writeCurrentDirectory() to write the changes made to the current directory back to the disk
    // ----------------------------------------------------------------------------------------------------------------------------------
    if (writeCurrentDirectory())
    {
        // 1. If error occurs, return non zero
        print("Error: writeCurrentDirectory failed!\n");
        return -3;
    }

    // vi. Set currentFile.isOpened to 0 (false)
    // ----------------------------------------------------------------------------------------------------------------------------------
    currentFile.isOpened = 0;

    return 0;
}

int deleteSubdirectory(char *directoryName)
{
    // i. Check to see if currentDirectory is opened, if not return with error code (i.e. return -1)
    // ----------------------------------------------------------------------------------------------------------------------------------
    if (!currentDirectory.isOpened) // guard: a directory must be open before we can delete inside it
    {
        print("Error: cannot delete a directory that is not open!\n");
        return -1;
    }

    // ii. Loop through the directory entries starting at currentDirectory.startingAddress and
    //     find the entry with filename of directoryName.
    // ----------------------------------------------------------------------------------------------------------------------------------

    // Count chars until null terminator
    int nameLength = 0;
    while (directoryName[nameLength] != 0)
        nameLength++;

    // Scan starting from first entry of currentDirectory while non-zero first byte
    directory_entry_t *dirEntry = (directory_entry_t *)currentDirectory.startingAddress;
    while (dirEntry->filename[0] != 0)
    {
        // Compare filename and verify directory (0x10), break if target subdirectory found
        if (stringcompare((char *)dirEntry->filename, directoryName, nameLength) && ((dirEntry->attributes & 0x10) == 0x10))
            break;

        dirEntry++; // Advance to the next 32-byte entry
    }

    // 1. If directoryName is not found, return non zero (if loop ended without breaking)
    if (dirEntry->filename[0] == 0)
    {
        print("Error: Subdirectory not found!\n");
        return -2;
    }

    // iii. Create a 512 byte buffer and load the subdirectory into it (we must check that the
    //      subdirectory is empty before continuing)
    //   1. Note: you only need to load the first cluster of the subdirectory since the first two
    //      entries should be "./" and "../" if the third directory is not empty, return non-zero
    // ----------------------------------------------------------------------------------------------------------------------------------
    uint8 subBuffer[512] = {0};                                                            // 512 byte buffer for the subdirectory's first cluster
    floppy_read(0, dirEntry->startingCluster + CLUSTER_TO_SECTOR, (void *)subBuffer, 512); // Read the subdirectory's first cluster from disk

    directory_entry_t *subEntries = (directory_entry_t *)subBuffer; // Convert buffer to directory entries

    // Error if the first user entry (at index 2) is not null (directory has children)
    if (subEntries[2].filename[0] != 0)
    {
        print("Error: Subdirectory is not empty!\n");
        return -3;
    }

    // iv. Overwrite all FAT clusters in the FAT table for this subdirectory with x0000
    // ----------------------------------------------------------------------------------------------------------------------------------
    uint16 cluster = dirEntry->startingCluster; // Start at target directory first cluster
    while (cluster != 0xFFFF)
    {
        uint16 next = fat0->clusters[cluster]; // Get next cluster before zeroing
        fat0->clusters[cluster] = 0x0000;      // Overwrite fat0 with 0
        fat1->clusters[cluster] = 0x0000;      // Overwrite fat1 with 0
        cluster = next;                        // Set next cluster
    }

    // v. Remove the directory entry that has the directoryName inside of it at currentDirectory.startingAddress
    //    by overwriting the first element with NULL (x00) or by overwriting entire directory entry with NULL
    // 1. Recommended: overwrite this directory entry with the last directory entry in the directory
    // ----------------------------------------------------------------------------------------------------------------------------------
    uint8 emptyEntry[32] = {0}; // Zeroed 32 byte buffer

    // Find last non-null entry before zeroing dirEntry
    uint32 maxEntries = currentDirectory.directoryEntry->fileSize / 32;              // Total possible entries in the parent directory
    directory_entry_t *base = (directory_entry_t *)currentDirectory.startingAddress; // Base pointer to the array of directory entries
    directory_entry_t *lastEntry = 0;                                                // Will track the last entry that is not null

    // Find last entry by checking if the first byte of the base directory is not null, then update lastEntry
    for (uint32 i = 0; i < maxEntries; i++)
        if (base[i].filename[0] != 0)
            lastEntry = &base[i];

    // Zero the deleted subdirectory's entry in memory
    *dirEntry = *(directory_entry_t *)emptyEntry;

    // Replace dirEntry with lastEntry when lastEntry unique and not null, then zero lastEntry
    if (lastEntry != 0 && lastEntry != dirEntry)
    {
        *dirEntry = *lastEntry;
        *lastEntry = *(directory_entry_t *)emptyEntry;
    }

    // vi. Call writeFATs() to write the changes made to the FATs back to the disk
    // ----------------------------------------------------------------------------------------------------------------------------------
    if (writeFATs())
    {
        print("Error: writeFATs failed!\n");

        // 1. If error occurs, return non zero
        return -4;
    }

    // vii. Call writeCurrentDirectory() to write the changes made to the current directory back to the disk
    //   1. If error occurs, return non zero
    // ----------------------------------------------------------------------------------------------------------------------------------
    if (writeCurrentDirectory())
    {
        print("Error: writeCurrentDirectory failed!\n");
        return -5;
    }

    return 0;
}
