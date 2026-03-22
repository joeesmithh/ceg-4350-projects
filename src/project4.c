#include "project4.h"

// FAT Copies
fat_t *fat0;
fat_t *fat1;

directory_t currentDirectory;         // The current directory we have opened
directory_entry_t rootDirectoryEntry; // The root directory's directory entry (this does not exist on the disk since the root is not inside of another directory)
file_t currentFile;                   // The current file we have opened

#if PROJECT == 4
int kernel()
{
    startkernel(startshell);
    return 0;
}
#endif

/**
 * Flushes both FAT copies to disk after verifying they are consistent.
 */
int writeFATs()
{
    // Loop through both FAT tables ensuring each entry is consistent between copies
    for (int i = 0; i < FAT_ENTRIES_MAX; i++)
    {
        uint16 fat0_entry = fat0->clusters[i];
        uint16 fat1_entry = fat1->clusters[i];

        // Check if the FAT tables are inconsistent
        if (fat0_entry != fat1_entry)
        {
            print("Error: FATs are inconsitent!\n");
            return 1;
        }
    }

    // Write both copies of the FAT tables back to disk
    int error = floppy_write(0, FAT0_SECTOR, (void *)fat0, FAT_SIZE);
    if (error)
    {
        print("Error: Could not write first FAT to disk!\n");
        return 1;
    }

    error = floppy_write(0, FAT1_SECTOR, (void *)fat1, FAT_SIZE);
    if (error)
    {
        print("Error: Could not write second FAT to disk!\n");
        return 1;
    }

    return 0;
}

/**
 * Writes the current directory back to its location on disk.
 */
int writeCurrentDirectory()
{
    // Check if the directory is opened
    if (!currentDirectory.isOpened)
    {
        print("Error: Can't write directory to disk! No directory is opened!\n");
        return 1;
    }

    // Check if this is the root directory (startingCluster == 0 means root)
    char isRootDirectory = currentDirectory.directoryEntry->startingCluster == 0;

    if (isRootDirectory)
    {
        // The root directory is at a fixed location on disk
        int error = floppy_write(0, ROOT_DIR_SECTOR, (void *)currentDirectory.startingAddress, ROOT_SIZE);
        if (error)
        {
            print("Error: Could not write root directory to disk!\n");
            return 1;
        }
    }
    else
    {
        // For subdirectories, write each sector by following the FAT chain
        uint16 cluster = currentDirectory.directoryEntry->startingCluster;
        uint8 *startingAddress = currentDirectory.startingAddress;
        uint16 sectorCount = 0;

        // Loop through every link in the FAT
        while (cluster != 0xFFFF)
        {
            // Convert the cluster to a sector
            uint32 sector = cluster + CLUSTER_TO_SECTOR;

            // Write the sector to the floppy disk
            floppy_write(0, sector, (void *)startingAddress + (512 * sectorCount), 512);
            sectorCount++;

            // Get the next cluster
            cluster = fat0->clusters[cluster];

            // Prevent infinite loop if FAT corrupted
            if (sectorCount > FAT_ENTRIES_MAX)
            {
                print("Error: The directory appears to be bigger than the entire floppy disk!\n");
                return 1;
            }
        }
    }

    return 0;
}

/**
 * Writes the current file back to disk, sector by sector, following the FAT chain.
 */
int writeCurrentFile()
{
    // Checks if the current file is opened
    if (!currentFile.isOpened)
    {
        print("Error: Can't write file to disk! No file is opened!\n");
        return 1;
    }

    // Starting at the first sector, each each sector from floppy into memory
    uint16 cluster = currentFile.directoryEntry->startingCluster;
    uint8 *startingAddress = currentFile.startingAddress;
    uint16 sectorCount = 0;

    // Loop through every link in the FAT
    while (cluster != 0xFFFF)
    {
        // Convert the cluster to a sector
        uint32 sector = cluster + CLUSTER_TO_SECTOR;

        // Write the sector to the floppy disk
        floppy_write(0, sector, (void *)startingAddress + (512 * sectorCount), 512);
        sectorCount++;

        // Get the next cluster
        cluster = fat0->clusters[cluster];

        // Prevent infinite loop if FAT corrupted
        if (sectorCount > FAT_ENTRIES_MAX)
        {
            print("Error: The file appears to be bigger than the entire floppy disk!\n");
            return -2;
        }
    }

    return 0;
}

/**
 * Frows or shrinks the cluster allocated to a file by modifying the FAT in memory.
 */
int resizeFile(uint16 startingCluster, uint32 newFileSize)
{
    // Loop through all clusters of the file
    uint16 cluster = startingCluster;
    uint16 count = 0;
    while (cluster != 0xFFFF)
    {
        // Count each cluster
        count++;

        // Go to the next cluster
        cluster = fat0->clusters[cluster];
    }

    // We have the file size
    uint32 currentFileSize = count * 512;

    // No resizing needed if desired file size is same as current
    if (currentFileSize == newFileSize)
        return 0;

    // File needs to grow: add more clusters in the FAT chain
    if (currentFileSize < newFileSize)
    {
        // Calculate how many clusters we need in total, accounting
        // for newFileSize not being a multiple of 512
        uint16 clustersNeeded = (newFileSize + 511) / 512;

        // Set last cluster in the chain
        uint16 lastCluster = startingCluster;
        while (fat0->clusters[lastCluster] != 0xFFFF)
        {
            lastCluster = fat0->clusters[lastCluster];
        }

        // Append new clusters until we have enough
        for (uint16 i = count; i < clustersNeeded; i++)
        {
            // Find a free cluster
            uint16 freeCluster = nextFreeCluster();
            if (freeCluster == 0xFFFF)
            {
                print("Error: Disk is full, cannot resize file!\n");
                return 1;
            }

            // Link the last cluster to the new free cluster in both FATs
            fat0->clusters[lastCluster] = freeCluster;
            fat1->clusters[lastCluster] = freeCluster;

            // Mark the new cluster as end of chain in both FATs
            fat0->clusters[freeCluster] = 0xFFFF;
            fat1->clusters[freeCluster] = 0xFFFF;

            // Advance to the newly added cluster
            lastCluster = freeCluster;
        }
    }

    // File needs to shrink: free extra clusters from the FAT chain
    if (currentFileSize > newFileSize)
    {
        // Calculate how many clusters we need in total, accounting
        // for newFileSize not being a multiple of 512
        uint16 clustersNeeded = (newFileSize + 511) / 512;
        if (clustersNeeded == 0)
            clustersNeeded = 1; // Keep at least one cluster

        // Get the cluster that should become the new last cluster
        uint16 current = startingCluster;
        for (uint16 i = 1; i < clustersNeeded; i++)
        {
            current = fat0->clusters[current];
        }

        // Free all clusters after the new last cluster
        uint16 toFree = fat0->clusters[current];

        // Mark the new last cluster as end of chain is both FATs
        fat0->clusters[current] = 0xFFFF;
        fat1->clusters[current] = 0xFFFF;

        // Free each cluster
        while (toFree != 0xFFFF)
        {
            uint16 next = fat0->clusters[toFree];

            // Mark cluster as free
            fat0->clusters[toFree] = 0x0000;
            fat1->clusters[toFree] = 0x0000;

            toFree = next;
        }
    }

    // Write FATs back to disk
    writeFATs();

    return 0;
}