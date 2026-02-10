#include "project4.h"

// FAT Copies
fat_t *fat0;
fat_t *fat1;

directory_t currentDirectory;  // The current directory we have opened
directory_entry_t rootDirectoryEntry;   // The root directory's directory entry (this does not exist on the disk since the root is not inside of another directory)
file_t currentFile;            // The current file we have opened

#if PROJECT == 4
int kernel()
{
    startkernel(startshell);
    return 0;
}
#endif

int writeFATs()
{
    (void) fat0; // Remove to disable unused variable warning
    (void) fat1; // Remove to disable unused variable warning
    return 0;
}

int writeCurrentDirectory()
{
    (void) currentDirectory; // Remove to disable unused variable warning
    (void) rootDirectoryEntry; // Remove to disable unused variable warning
    return 0;
}

int writeCurrentFile()
{
    (void) currentFile; // Remove to disable unused variable warning
    return 0;
}

int resizeFile(uint16 startingCluster, uint32 newFileSize)
{
    (void) startingCluster; // Remove to disable unused parameter warning
    (void) newFileSize; // Remove to disable unused parameter warning
    return 0;
}