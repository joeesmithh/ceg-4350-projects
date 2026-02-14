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

// Print A once
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

// Print C four times, yielding between each print
void procc()
{
    putchar('C');
    yield();
    putchar('C');
    yield();
    putchar('C');
    yield();
    putchar('C');
    exit();
}

// Print D three times, yielding between each print
void procd()
{
    putchar('D');
    yield();
    putchar('D');
    yield();
    putchar('D');
    exit();
}

// Print E twice, yielding between each print
void proce()
{
    putchar('E');
    yield();
    putchar('E');
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
    // Create 5 user processes with unique stack addresses
    createuserprocess(proca, (void *)0x10000);
    createuserprocess(procb, (void *)0x11000);
    createuserprocess(procc, (void *)0x12000);
    createuserprocess(procd, (void *)0x13000);
    createuserprocess(proce, (void *)0x14000);

    print("Kernel process has started...\n");

    // Schedule the next process
    int userprocs = ready_process_count();

    // As long as we have ready user processes to run, yield to them
    while (userprocs > 0)
    {
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

void schedule()
{
    // Start searching from the PID after the previously run user process
    // If no previous process exists, start from the beginning
    int start = 0;
    if (prevprocess != 0)
    {
        start = prevprocess->pid + 1;
    }

    // Round robin search all processes
    for (int i = 0; i < MAX_PROCS; i++)
    {
        int pid = (start + i) % MAX_PROCS; // PID of next process
        proc_t *current = &processes[pid]; // Get process with the PID

        // Only select user processes that are ready to run
        if (current->type == PROC_TYPE_USER && current->status == PROC_STATUS_READY)
        {
            nextprocess = current;
            return 1; // Found a ready user process
        }
    }

    // No ready user processes found
    return 0;
}

void yield()
{
    // Set the running process' status as ready to run again
    runningprocess->status = PROC_STATUS_READY;

    // If we are yielding a user process
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

    // Context switch to next process, executes whatever next process is pointing at
    contextswitch();

    return;
}

void exit()
{
    // If the running process is a user process, terminate it and switch to kernel
    if (runningprocess->type == PROC_TYPE_USER)
    {
        // Mark the current process as terminated so it won't be scheduled again
        runningprocess->status = PROC_STATUS_TERMINATED;

        // Select the kernel process to run next
        nextprocess = kernelprocess;

        // Context switch to the kernel process
        contextswitch();
    }

    // If the kernel process calls exit, simply return (ends the OS)
    return;
}

int createuserprocess(void *func, char *stack)
{
    // If we have filled our process array, return -1
    if (process_index >= MAX_PROCS)
        return -1;

    proc_t userproc;                     // Create a new user process
    userproc.status = PROC_STATUS_READY; // User processes start in ready state
    userproc.type = PROC_TYPE_USER;      // Mark as a user process
    userproc.esp = stack;                // Set stack pointer to stack address
    userproc.ebp = stack;                // Set base pointer to stack address
    userproc.eip = func;                 // Set instruction pointer to the function entry point

    // Assign a PID and store the process in the process array
    userproc.pid = process_index;
    processes[process_index] = userproc;
    process_index++;

    // Process successfully created
    return 0;
}