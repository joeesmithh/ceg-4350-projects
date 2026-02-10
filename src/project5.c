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
    (void) subdirectoryName; // Remove to disable unused parameter warning
    return 0;
}

int openDirectory(char *directoryName)
{
    (void) directoryName; // Remove to disable unused parameter warning
    return 0;
}