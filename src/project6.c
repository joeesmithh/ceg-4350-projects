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
    return 0;
}

int deleteSubdirectory(char *directoryName)
{
    (void) directoryName; // Remove to disable unused parameter warning
    return 0;
}