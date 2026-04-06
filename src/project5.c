#include "project5.h"

#if PROJECT == 5
int kernel()
{
    startkernel(startshell);
    return 0;
}
#endif

int createSubdirectory(char *subdirectoryName)
{
    // i. Checks if the current directory is opened
    if (!currentDirectory.isOpened)
    {
        // 1. If currentDirectory is not opened, print an error message, return non-zero value
        print("Error: cannot create a subdirectory inside of a directory that is not open!");
        return -1;
    }

    // ii. Find the next free directory entry inside of the currentDirectory
    directory_entry_t *currentEntry = (directory_entry_t *)currentDirectory.startingAddress;
    uint32 bytesNeeded = 32;

    // 1. Loop through currentDirectory.startingAddress until a directory_entry_t is found with filename[0] == 0
    while (currentEntry->filename[0] != 0)
    {
        currentEntry++;
        bytesNeeded += 32;
    }

    // iii. Check to see if the directory that you are creating this subdirectory in needs to be resized
    if (bytesNeeded > currentDirectory.directoryEntry->fileSize)
    {
        resizeFile(currentDirectory.directoryEntry->startingCluster, bytesNeeded);
    }

    // iv. Find the next free cluster in the FAT and mark it as EOF
    uint16 next = nextFreeCluster();
    fat0->clusters[next] = 0xFFFF;
    fat1->clusters[next] = 0xFFFF;

    // 2. Next, write the FATs to disk using writeFATs()
    writeFATs();

    // v. Using the free entry found in step ii:

    // 1. Set filename to the subdirectoryName argument
    stringcopy(subdirectoryName, (char *)currentEntry->filename, 8);

    // 2. Set extension to "   " (subdirectories have no extension)
    stringcopy("   ", (char *)currentEntry->ext, 3);

    // 3. Set attributes to 0x10 (labeled as subdirectory)
    currentEntry->attributes = 0x10;

    // 4. Set starting cluster to the next free cluster found in step iv
    currentEntry->startingCluster = next;

    // 5. Set the file size to 512 (one cluster)
    currentEntry->fileSize = 512;

    // 6. Write the currentDirectory to the disk using writeCurrentDirectory()
    writeCurrentDirectory();

    // vi. Create a buffer for the new sector for the subdirectory and add:

    // 1. Add an entry for "./" containing the directory entry for the subdirectory itself
    // 2. Add an entry for "../" containing the directory entry for the currentDirectory
    // 3. Write the buffer to the disk:

    // a. char buffer[512] = {0};
    char buffer[512] = {0};

    // b. directory_entry_t *selfEntry = (directory_entry_t *)buffer;
    // selfEntry is the first entry in the cluster, the "./" (self) entry
    directory_entry_t *selfEntry = (directory_entry_t *)buffer;

    // c. directory_entry_t *parentEntry = ((directory_entry_t *)buffer) + 1;
    // parentEntry is the second entry, the "../" (parent) entry
    directory_entry_t *parentEntry = ((directory_entry_t *)buffer) + 1;

    // d. modify the parent and self here
    // Self entry "./" points back to this subdirectory's own cluster
    // Using 8-char string so stringcopy fills all 8 filename bytes
    stringcopy((char *)"./      ", (char *)selfEntry->filename, 8);
    selfEntry->attributes = 0x10;      // Directory attribute
    selfEntry->startingCluster = next; // Points to itself
    selfEntry->fileSize = 512;

    // e. set parent name to "../"
    // f. stringcopy((char *)"../     ", (char *)parentEntry->filename, 8);
    stringcopy((char *)"../     ", (char *)parentEntry->filename, 8);
    parentEntry->attributes = 0x10; // Directory attribute

    // If the parent is the root directory, startingCluster is 0
    // Set automatically because rootDirectoryEntry.startingCluster is always 0
    parentEntry->startingCluster = currentDirectory.directoryEntry->startingCluster;
    parentEntry->fileSize = 512;

    // g. floppy_write(0, next + CLUSTER_TO_SECTOR, (void *) buffer, 512);
    floppy_write(0, next + CLUSTER_TO_SECTOR, (void *)buffer, 512);

    // vii. Return 0 if no errors have occurred in any of the previous steps
    return 0;
}

int openDirectory(char *directoryName)
{
    // i. Checks if the current directory is opened
    if (!currentDirectory.isOpened)
    {
        // 1. If currentDirectory is not opened, print an error message, return non-zero value
        print("Error: cannot navigate to a subdirectory inside of a directory that is not open!");
        return -1;
    }

    // ii. Checks if the currentFile is opened
    if (currentFile.isOpened)
    {
        // 1. If currentFile is opened, print an error message, return non-zero value
        print("Error: cannot open a directory while a file is open!\n");
        return -1;
    }

    //  iii. Find the directory entry that has the name directoryName (use char stringcompare() in string.c like in fat.c in openFile())
    // 1. Loop through currentDirectory.startingAddress until a directory_entry_t is found with filename equal to directoryName and attributes with the 0x10 bit set
    // 2. Hint: you can reuse some sections of openFile() to do this

    // Get a pointer to the first address of the directory entry in this directory
    directory_entry_t *directoryEntry = (directory_entry_t *)currentDirectory.startingAddress;

    // Create a filename padded with spaces
    int nameLength = 0;
    while (directoryName[nameLength] != 0)
    {
        nameLength++;
    }

    // Loop through entries until a match is found or we hit a null entry (end of directory)
    char fileExists = 0;
    while (directoryEntry->filename[0] != 0)
    {
        // Match on filename (space-padded) AND the directory attribute bit (0x10)
        // Directories have no extension, so we do not compare the ext field
        fileExists = stringcompare((char *)directoryEntry->filename, directoryName, nameLength) &&
                     ((directoryEntry->attributes & 0x10) == 0x10);

        // If we found the directory we can stop looping!
        if (fileExists)
        {
            break;
        }

        directoryEntry++;
    }

    // If no matching directory was found, report an error
    if (!fileExists)
    {
        print("Error: Directory not found!\n");
        return -1;
    }

    // iv. Checks if we are opening the root directory (i.e.: directoryEntry->startingCluster == 0)
    // startingCluster == 0 is root, used by "../" entries with parent as root
    if (directoryEntry->startingCluster == 0)
    {
        // 1. If we are opening the root directory, set currentDirectory.directoryEntry to root directory entry:
        // a. currentDirectory.directoryEntry = &rootDirectoryEntry;
        currentDirectory.directoryEntry = &rootDirectoryEntry;

        // 2. Read the root directory from the disk:
        // a. readFailed = floppy_read(0, ROOT_DIR_SECTOR, (void*)currentDirectory.startingAddress, ROOT_SIZE);
        floppy_read(0, ROOT_DIR_SECTOR, (void *)currentDirectory.startingAddress, ROOT_SIZE);
    }

    // v. If we are opening a non-root directory:
    else
    {
        // 1. Load the directory off of the disk by traversing the FATs from the directory entry's startingCluster found in step iii
        // a. Read each 512 byte cluster into currentDirectory.startingAddress + 512 * index
        uint16 cluster = directoryEntry->startingCluster;
        uint16 sectorCount = 0;

        while (cluster != 0xFFFF)
        {
            uint32 sector = cluster + CLUSTER_TO_SECTOR;
            floppy_read(0, sector, (void *)currentDirectory.startingAddress + (512 * sectorCount), 512);
            sectorCount++;

            // Advance to next cluster in the FAT chain
            cluster = fat0->clusters[cluster];

            // Prevent infinite loop
            if (sectorCount > FAT_ENTRIES_MAX)
            {
                print("Error: Directory FAT chain is larger than the entire floppy disk!\n");
                return -1;
            }
        }

        // 2. Once the directory has been loaded into memory, search for the selfEntry that has filename "./" and set currentDirectory.directoryEntry = selfEntry;
        directory_entry_t *loadedEntry = (directory_entry_t *)currentDirectory.startingAddress;
        char selfFound = 0;

        while (loadedEntry->filename[0] != 0)
        {
            // Self-entry is identified by '.' at [0] and '/' at [1] with the directory attribute
            if (loadedEntry->filename[0] == '.' &&
                loadedEntry->filename[1] == '/' &&
                ((loadedEntry->attributes & 0x10) == 0x10))
            {
                currentDirectory.directoryEntry = loadedEntry;
                selfFound = 1;
                break;
            }
            loadedEntry++;
        }

        if (!selfFound)
        {
            print("Error: Could not find self entry in the loaded subdirectory!\n");
            return -1;
        }
    }

    // vi. Return 0 if no errors have occurred in any of the previous steps
    return 0;
}