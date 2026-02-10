#include "project3.h"
#include "multitasking.h"
#include "processes.h"

// An array to hold all of the processes we create
proc_t processes[MAX_PROCS];

// Keep track of the next index to place a newly created process in the process array
uint8 process_index = 0;

proc_t *prevprocess = 0; // The previously ran user process
proc_t *runningprocess;  // The currently running process, can be either kernel or user process
proc_t *nextprocess;     // The next process to run
proc_t *kernelprocess;   // The kernel process

#if PROJECT == 3

void proca()
{
    putchar('A');
    exit();
}

void procb()
{
    putchar('B');
    yield();
    putchar('B');
    exit();
}

/*
    1. Creates 5 user processes
    2. Prints a start up message
    3. Loops, yielding to the next user process
    4. When there are no more ready user processes, print a termination message and return
    5. returns nothing
    6. NOTE: The kernel process should run in between each user process yielding so that
        the kernel process can perform the scheduling. Technically, the order in which
        processes should execute is:
            A -> Kernel -> B -> Kernel -> C -> Kernel -> D -> Kernel -> E -> Kernel -> B -> ...
*/
void prockernel()
{
    print("Kernel process has started...\n");

    // Create the user processes
    createuserprocess(proca, (void *)0x10000);
    createuserprocess(procb, (void *)0x11000);
    // createuserprocess(procc, (void *) 0x12000); // Creates a stack in memory for process to use
    // createuserprocess(procd, (void *) 0x13000); // Creates a stack in memory for process to use
    // createuserprocess(proce, (void *) 0x14000); // Creates a stack in memory for process to use

    // Schedule the next process
    int userprocs = ready_process_count();

    // As long as we have ready user processes to run
    while (userprocs > 0)
    {
        // Yield to them
        yield();
        userprocs = ready_process_count();
    }

    print("\nKernel process has exited...\n");
    exit();
}

int kernel()
{
    startkernel(prockernel);
    return 0;
}

#endif

void yield()
{
    // Set the running process' status as ready to run again
    runningprocess->status = PROC_STATUS_READY;

    // If we are yielding a use process
    if (runningprocess->type == PROC_TYPE_USER)
    {
        // Track the prev user process to help with scheduling
        prevprocess = runningprocess;

        // Select the kernel to run next
        nextprocess = kernelprocess;
    }
    else if (runningprocess->type == PROC_TYPE_KERNEL)
    {
        // Call schedule function to select nextprocess algorithmically
        schedule();
    }

    // Context switch to next process, executes whatever next
    // process is pointing at
    contextswitch();

    return;
}

void exit()
{
    return;
}

int createuserprocess(void *func, char *stack)
{
    proc_t userproc;
    userproc.esp = stack;
    userproc.ebp = stack;

    // Everything is almost identical to the startkernel() method

    return 0;
}

void schedule()
{
    return;
}