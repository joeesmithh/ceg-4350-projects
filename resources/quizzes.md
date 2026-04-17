# CEG 4350 Quizzes

## Table of Contents
- [CEG 4350 Quizzes](#ceg-4350-quizzes)
  - [Table of Contents](#table-of-contents)
  - [Quiz 1 (Introduction)](#quiz-1-introduction)
  - [Quiz 2 (Hardware and the OS)](#quiz-2-hardware-and-the-os)
  - [Quiz 3 (Hardware and the OS)](#quiz-3-hardware-and-the-os)
  - [Quiz 4 (Processes and Threads)](#quiz-4-processes-and-threads)
  - [Quiz 5 (Processes and Threads)](#quiz-5-processes-and-threads)
  - [Quiz 6 (Processes and Threads)](#quiz-6-processes-and-threads)
  - [Quiz 7 (CPU Scheduling)](#quiz-7-cpu-scheduling)
  - [Quiz 8 (Main Memory)](#quiz-8-main-memory)
  - [Quiz 9 (Main Memory)](#quiz-9-main-memory)
  - [Quiz 10 (Memory Allocation)](#quiz-10-memory-allocation)
  - [Quiz 11 (File Systems)](#quiz-11-file-systems)
  - [Quiz 12 (File Systems)](#quiz-12-file-systems)
  - [Quiz 13 (File Systems)](#quiz-13-file-systems)
  - [Quiz 14 (Main Memory)](#quiz-14-main-memory)
  - [Quiz 15 (File Systems and Input \& Output)](#quiz-15-file-systems-and-input--output)
  - [Quiz 16 (Input \& Output)](#quiz-16-input--output)
  - [Quiz 17 (Input \& Output)](#quiz-17-input--output)
  - [Quiz 18 (Input \& Output)](#quiz-18-input--output)
  - [Quiz 19 (Input, Output, and Distributed Systems)](#quiz-19-input-output-and-distributed-systems)
  - [Quiz 20 (Distributed Systems)](#quiz-20-distributed-systems)
  - [Quiz 21 (Networks)](#quiz-21-networks)
  - [Quiz 22 (Networks)](#quiz-22-networks)
  - [Quiz 23 (Networks)](#quiz-23-networks)


## Quiz 1 (Introduction)

1. **What are the dates and room numbers of the midterm exam and final exam? How did you find this information?**

    - Midterm Exam - Friday, February 27th 2026 at 11:15 am - 12:10 pm in RC 144
    - Final Exam - Friday, May 1st 2026 at 10:15 am - 12:15 prn in RC 144
    
    I found it in the syllabus.

2. **What is the academic misconduct policy for this class?**

    All assignments are to be completed individually. Sharing your work or copying someone else's work, including using Al generated work, will result in a O for the assignment(s) and a formal Academic Integrity Violation will be submitted. The university policy on academic misconduct can be found at: https://policy.wright.edu/policy/3710-academic-integrity-standards-and-process-misconduct

3. **What are ways that I can make lecture more fun, interesting, enjoyable, or better?**

    no idea

## Quiz 2 (Hardware and the OS)

1. **What is the job of an operating system?**

    The operating system provides an environment for programs to run and managing the access of the hardware as programs request it. When access to the hardware is necessary, the OS goes through the kernel (a part of the operating system) to do so.

2. **What is the job of the kernel in an operating system?**

    The job of the kernel is is to manage the hardware directly on behalf of the user programs and OS. The kernel directly interfaces with hardware and manages the access of the hardware and lives in a protected environment to properly protect the hardware.

3. **How does a user program get access to the hardware from the kernel?**

    A user program gets access to the hardware via system calls. System calls are interrupts that contain code that exists in the protected area of the operating system in the kernel. These system calls interface with the hardware in a defined way that can't be circumvented by the user programs.

## Quiz 3 (Hardware and the OS)

1. **Where can the bootloader be found? What does the bootloader do?**

    The bootloader is found on the first sector (master boot record) of the bootable disk identified by the BIOS or UEFI. The bootloader is designed to, at a bare minimum, load your operating system from the disk into memory and begin running it.

2. **Why do keyboards send scancodes and not ASCII characters?**

    Keyboards send scancodes and not ASCII characters because most keys on the keyboard do not have ASCII equivalents. For example, the ALT key does not have an appropriate ASCII value. Also, if a key is released, there aren't appropriate scancodes either. Characters from other languages also don't have ASCII equivalents!

3. **Write an if statement that checks if the keyboard status port is ready. If it  is, print `"Ready!"` if not, print `"Not ready!"` Hint: use the bitwise AND operation (`&`) to check specific bits. Note: use the `uint8 inb(uint16 port)` function that is inside your project for accessing the status port.**

    ```c
    uint8 status = inb(0x64);

    // If the least significant bit of 'status' is 1
    if(status & 0x01)
    {
        print("Ready!");
    }
    else 
    {
        print("Not ready!");
    }
    ```

## Quiz 4 (Processes and Threads)

1. **What is context switching?**

    Context switching is when the OS switches the user process that is currently running. For example, if Notepad++ is currently running and it then waits for the keyboard input, it is more useful for the OS to context switch to another process like `gcc` to allow `gcc` to make progress.

2. **What is the difference between a program and a process? Why does the OS have a process abstraction?**

    A program is an executable file that contains the machine language necessary to run. A process is just an instance of that program running.
    
    For example, a web browser has an executable file, but you can run multiple processes of that web browser to get multiple browser windows.
    
    The OS has a process abstraction to allow for a defined way of creating processes, terminating processes, and managing processes' resources.

3. **How do multiple processes in an OS execute when there is only one CPU? Are they executing simultaneously?**

    Multiple processes run on a single CPU through context switching. They are not actually executing simultaneously, they are constantly being swapped between.

## Quiz 5 (Processes and Threads)

1. **What does *preemptive* mean when referring to multitasking? How does it differ from *cooperative*?**

    Preemptive refers to a type of multitasking where the OS can preempt or stop a user process from running without the user process' say.
    
    Cooperative refers to a type of multitasking where the processes get to decide when they yield, or give up access to the CPU, for another process to run.
    
    The difference lies in who gets to decide when the process pauses, preemptive for the OS to decide, cooperative for the user process to decide.

2. **What are all the states a process can be in and what does each state mean?**

    - **New** - A process is newly created and needs to be set up and have resources allocated to it by the OS
    - **Ready** - A process has everything it needs to run on the CPU but is not actively running
    - **Running** - A process is actively running on a CPU
    - **Waiting** - A process is waiting for something before it can be ready to run again, ex: pending IO request or event
    - **Terminated** - A process is done running and the OS needs to deallocate its resources

3. **Are there any issues if an OS context switches very frequently? Are there any issues if an OS context switches very infrequently?**

    If an OS context switches very frequently, it may spend most of its time context switching rather than executing the instructions in our user processes.
    
    If an OS context switches very infrequently, it may spend too much time on an individual process which would cause the OS to appear to run very slow to the user.

## Quiz 6 (Processes and Threads)

1. **What is the difference between a process and a thread?**

    A process is an instance of a running program. This program can create many threads inside of it that can execute portions of the code in parallel. The difference is that a process is a single instance of a program, a thread is a part of that instance that gets created to run.

2. **In the *many-to-one* thread model, can all of the CPU cores be utilized? Why or why not?**

    No, in the many-to-one thread model, not all cores can be utilized. The reason why is because if you have 4 cores and 2 processes, 2 of the cores will have nothing to do. This is because each process is mapped to only 1 kernel thread and therefore only runs on one core at a time.
    
    Technically, if you have >=n number of processes and n number of CPU cores they can all be utilized.

3. **In modern operating systems, what is usually scheduled to run on the CPU? Threads or processes?**

    Threads are normally scheduled to run on the CPU in modern operating systems rather than processes themselves. Data that is associated with the process that created the threads may be used to determine which threads should be scheduled though.

## Quiz 7 (CPU Scheduling)

| 1.  | PID | Arrival Time | Burst Time |
| --- | --- | ------------ |
| P1  | 0   | 4            |
| P2  | 2   | 4            |
| P3  | 5   | 2            |
    
    **Using the table above, use the FIFO (First-In-First-Out) scheduling algorithm to calculate the average waiting time for all processes.**

    ---

    **P1:** 0 -> 4 (0 left)<br>
    **P2:** 2 -> 4 (4 left) -> 8 (0 left)<br>
    **P3:** 5 -> 8 (2 left) -> 10 (0 left)

    **P1 Turnaround:** 4<br>
    **P2 Turnaround: 8** - 2 = 6<br>
    **P3 Turnaround:** 10 - 5 = 5

    **P1 Wait:** 4 - 4 = 0<br>
    **P2 Wait:** 6 - 4 = 2<br>
    **P3 Wait:** 5 - 3 = 3<br>
    
    **Average wait:** (0 + 2 + 3) / 3 = 1.67

| 2.  | PID | Arrival Time | Burst Time |
| --- | --- | ------------ |
| P1  | 0   | 6            |
| P2  | 1   | 4            |
| P3  | 2   | 3            |

    **Using the table above, use the Round Robin scheduling algorithm with quanta = 2 to calculate the average waiting time for all processes.**

    ---

    **P1:** 0 -> 2 (4 left) .. 6 -> 8 (2 left) .. 11 -> 13 (0 left)<br>
    **P2:** 1 .. 2 -> 4 (2 left) .. 8 -> 10 (0 left)<br>
    **P3:** 2 .. 4 -> 6 (1 left) .. 10 -> 11 (0 left)

    **P1 Turnaround:** 13 - 0 = 13<br>
    **P2 Turnaround:** 10 - 1 = 9<br>
    **P3 Turnaround:** 11 - 2 = 9

    **P1 Wait:** 13 - 6 = 7<br>
    **P2 Wait:** 9 - 4 = 5<br>
    **P3 Wait:** 9 - 3 = 6

    **Average Wait:** (7 + 5 + 6) / 3 = 18/3 = 6

| 3.  | PID | Arrival Time | Burst Time |
| --- | --- | ------------ |
| P1  | 0   | 8            |
| P2  | 3   | 2            |
| P3  | 2   | 4            |

    **Using the table above, use the Shortest Remaining Time (preemtive) scheduling algorithm to calculate the average waiting time for all processes.**

    **Explain why or why not the average waiting time could be improved by selecting a different scheduling algorithm with the processes provided.**

    ---

    **P1:** 0 -> 2 (6 left) .. 8 -> 14 (0 left)<br>
    **P2:** 3 -> 5 (0 left)<br>
    **P3:** 2 -> 3 (3 left) .. 5 -> 8 (0 left)

    **P1 Turnaround:** 14 - 0 = 14<br>
    **P2 Turnaround:** 5 - 3 = 2<br>
    **P3 Turnaround:** 8 - 2 = 6

    **P1 Wait:** 14 - 8 = 6<br>
    **P2 Wait:** 2 - 2 = 0<br>
    **P3 Wait:** 6 - 4 = 2

    **Average Wait:** (6 + 0 + 2) / 3 = 2.67

    The average waiting time can not be improved, because this is the optimal scheduling algorithm for this metric.

## Quiz 8 (Main Memory)

1. **Why is MLFQ an adaptive scheduling algorithm?**

    MLFQ is adaptive because it changes the priority of processes based on their past performance. For example, if a process exceeds its quanta, it is moved down in priority. This makes the scheduling algorithm adapt to the performance of the processes at any point in time.

2. **Why is MLFQ used instead of SPN? Isn't SPN optimal? How could MLFQ be better?**

    SPN is optimal for minimizing waiting time. However, SPN is impractical because it is impossible to know the actual burst time of a process in the real world. Therefore, MLFQ is better because it adapts to the measured burst times of processes dynamically since the burst times are unknown. Thus, MLFQ closely approximates the performance of SPN.

3. **Assume short processes get 20 tickets and long processes get 5 tickets when using a lottery scheduling algorithm.**
    
    **What is the CPU utilization of a single short process if there are 10 short processes and 20 long processes?**

    - 20 tickets * 10 short processes = 200 tickets for all short processes
    - 5 tickets * 20 long processes = 100 tickets for all long processes
    - 200 + 100 = 300 total tickets
    - 20 tickets for a single short process / 300 total tickets = 1/15 = 6.67% CPU utilization per short process

## Quiz 9 (Main Memory)

1. **Where does a program exist before you run it? Where does it exist after you run it?**

    A program exists on your storage device before you run it as a file in your file system. At this point it is just a dormant program and cannot be executed until it is loaded into memory.
    
    A program is then copied into memory after you run it and it exists in memory. At this point it becomes a process and your OS will execute the process as it exists in memory.

2. **What is the difference between a virtual (logical) address and a physical address?**

    A virtual address is the address that the process uses to access memory. Virtual addresses start from the beginning of the process and end at the end of the process.
    
    A physical address is the address sent to RAM to access a physical location in the RAM's hardware. Physical addresses start from the beginning of physical RAM and end at the end of physical RAM.

3. **In dynamic relocation, what do the base and limit registers do? Why are they needed?**

    In dynamic relocation, the base register is used to translate virtual addresses into physical addresses by acting as an offset. The limit register is used to ensure the virtual address does not overreach and exceed the memory region that the process is allowed to access.

## Quiz 10 (Memory Allocation)

1. **Why might an OS use the "worst fit" memory allocation algorithm? If it is the worst fit, why would it ever be used?**

    Worst means that the largest gap in memory is left over when allocating a new process.

    This might be used if you have very small processes that often fit in these gaps. You may also use this if you want to ensure a process can grow at some point in the future.

2. **What is external fragmentation and why is it an issue?**

    External fragmentation refers to when processes have unused memory between them. It is an issue because if these gaps are numerous and small, there may not be a large enough contiguous location to put new processes, even though the sum of their memory is enough to fit a process.

3. **Is compaction necessary when using paging? Why or why not?**

    Compaction is not necessary when using paging. The reason why is as long as there is enough pages available it is possible to allocate the entire process in memory non-contiguously. The process can be split up into fixed sized chunks and as long as you have enough free chunks in memory, the process can be spread all across memory.

## Quiz 11 (File Systems)

1. **What is an inode?**

    An inode data structure that contains information necessary for locating the clusters of a file on the storage device. If the inode gets lost or corrupted, you will not be able to find the file on the storage device even though the data may still physically exist on the storage device.

2. **Where is an inode stored? Why?**

    The inode is located on the storage device before it is read into memory. The reason why is because the keeps track of the clusters of a file which allows you to retrieve the file from the storage. If the was not on the storage device, the inode would be lost when restarting the computer, thus never allowing you to find your files.

3. **What is the linked allocation method for storing files?**

    The linked allocation method uses an that is a linked list. The start of the linked list or inode tells you the starting cluster of the file. If you traverse the linked list you can retrieve all of the clusters associated with the file.

## Quiz 12 (File Systems)

1. **What's a benefit of linked allocation? What's a downside of linked allocation?**

    The benefit of linked allocation is that your storage device can have all of its clusters fully utilized because the clusters of a file are not required to be contiguous. This means that if you have 3 free non-contiguous clusters, you can still allocate a file requiring 3 clusters to these sectors.

    The downside of linked allocation is that clusters are not required to be contiguous. This means that it it is possible to have your files spread across many random sectors which makes the reading and writing of the file a slow process.

2. **In a FAT file system, how do you find the starting cluster of a file?**

    In the FAT file system the starting cluster of a file is stored inside of the directory entry for that file. Each directory in the FAT file system is split into 32 byte chunks called directory entries. Each directory entry that contains the metadata of a valid file includes the starting cluster the file occupies. If you get this cluster and follow the links in the FAT table you can access all clusters allocated to the file.

3. **What is an advantage of extent-based allocation over linked allocation?**

    The main advantage of extent-based allocation over linked allocation is that the inode requires very little data and the clusters of the file are guaranteed to be contiguous. In extent-based allocation, the inode only contains the starting cluster and the number of clusters afterwards that the file takes up. This means the file must be stored in contiguous clusters, otherwise it could not be accessed with just this data.

## Quiz 13 (File Systems)

1. **What is the purpose of a file system? Why don't we just access the sectors directly off of our storage devices?**

    Files are made up of many sectors on our storage device. The file system gives users a safe and easy to use inerface for accessing files whether that is reading, writing, deleting, or creating files.

    The purpose of the file system is to exist as an abstraction of the sectors on our system. To the general user, they do not care what sectors a file occupies. At the most, a general user will most likely only care if the strage device has enough space on it or not to hold the file.

2. **What is an atomic unit? Are the atomic units for RAM and storage different"**

    An atomic unit refers to the smallest size of data that is able to be accessed for a specific device. For example, the storage device's atomic unit is 1 sector (512) bytes. Another example is memory, where memory's atomic unit is 1 byte (8 bits).

    Every tiem you want to access data from a storage device, you have to access the entire 512 byte sector. Every tiem you want to access data from memory, you have to access the entire 8 bit memory location.

3. **In the FAT file system, what do directories contain? What is the format?**

    In the FAT file system, directories contain directory entries. These directory entries contain all of the metadata required for a specific file such as file size, starting cluster, creation data, file name, etc.

    The format of a directory is fixed to 32 bytes, with metadata in this order:
    - File Name
    - Extension
    - Attributes
    - Reserved
    - Creation Time
    - Creation Date
    - Last Access Date
    - Ignore
    - Last Write Time
    - Last Write Date
    - First Cluster
    - File Size

## Quiz 14 (Main Memory)

1. **What is a TLB? Why is it used instead of registers or memory?**

    The TLB is the Translation Look-aside Buffer. It is a cache that stores a portion of our page table.

    The TLB is used to store a portion of our page table because if our page table is lways accessed from memory it would be very slow. If our page table was always accessed from registers it would be limiting because registers take up a lot of hardware and have a fixed quantity.

2. **Why would you invalidate or flush the TLB?**

    Whenever a context switch is performed the TLB no longer contains a valid page table for the process that was context switched to.

    For this reason, we would want to invalidate or flush the TLB so that an incorrect page is not accessed by the process.

3. **What is segmentation and how do base and limit registers apply?**

    Segmentation is when a process is split into many different discrete segments. For example, a process is generally made up of a code segment, a data segment, a stack segment, a heap segment, and so on.

    Base and limit registers are used to define the regions of these segments. For example, each segment that the process is made up of can have a base starting address and a limit address.

## Quiz 15 (File Systems and Input & Output)

1. **Where do "." and ".." come from when you are navigating directories?**

    The "." and ".." directories are stored inside of the directory entry itself "." is the directory entry of the directory itself, ".." is the directory entry to the parent. 
    
    Since these are located inside of the directory itself, it makes it easy to navigate back to the parent directory if one exists since you can always grab the reference from the contents of the directory that you currently have opened.

2. **What problems were there with the original Unix file system organization?**

    The original Unix file system suffered from small cluster sizes and poor clustering.
    
    Small cluster sizes were an issue because many files were much larger than 512 bytes, which often left tiny clusters made of 1 sector scattered all over the disk. This issue was remedied by increasing the cluster size to 4096.
    
    Poor clustering was an issue because the inodes and file data was not organized nearby each other which forced the hard drive to seek many times to access data. This issue was remedied by collocating all file clusters and inodes within the same cylinder.

3. **What are the different types of device ports? What do they do?**

    The different device ports are:
    
    - Status - reports the current status or state that the IO device is in and if there is any error
    - Input - provides data from the input device to the CPU
    - Output - provides data from the CPU to the output device
    - Control - configures the IO device, such as setting the state of the device or giving the device more information for a future operation

## Quiz 16 (Input & Output)

1. **What is the purpose of a device driver?**

    A device driver is a piece of software that is written to send and receive data from devices and to control devices. This is handled by communicating directly with the device via IO ports. Device drivers exist so that user programs are not required to implement custom communicatio schemes for accessing devices and since the device drivers are controlled by the OS it is a safe way of allowing for device access rather than directly.

2. **When is it acceptable to access ports directly?**

    It is only acceptable to access IO ports directly if you are writing a low level operating system or if you are writing a device driver. Accessing ports directly is dangerous if done outside of the OS's protections and may not even be possible depending on the hardware.

3. **What is a device controller (hardware) responsible for?**

    A device controller is responsible for sending messages on the bus and for receiving messages on the bus. It is also responsible for acting upon the actual underlying device itself. For example, if the controller reads a message off the bus telling it to spin the motor in the hard drive, it must control the electrical systems necessary to do so.

## Quiz 17 (Input & Output)

1. **When is direct memory access useful?**

    Direct memory access (DMA) is useful when you have devices that want to send large blocks of data, like the storage device.

    If the CPU was involved in transferring every individual byte, it would result in a lot of wasted CPU resources. So instead, the DMA controller is responsible for transferring the individual bytes, without the CPU's involvement.

2. **How do the CPU and DMA compete? Isn't DMA supposed to make the CPU's job easier?**

    CPU and DMA compete over the memory bus. This is because the DMA controller wants to read/write large amounts of data to memory and the CPU needs to access memory to get instructions and data to continue running.

    Only the DMA or CPU can use the memory bus at a time, not both, so they compete for this access.

    Overall, since the CPU has a cache, it is very likely that the CPU will spend a lot of time not needing to access memory, during this time, the DMA controller can utilize memory and the bus.

3. **What is a reason to have a buffer inside of the kernel?**

    A reason to have a buffer inside of the kernel is to package things up before they are delivered to a user process. For example, a user process may not want to be bombarded with a trickle of bytes from the network that come in irregular bursts, instead, the kernel can buffer them and send only when there is a sufficient amount of data to send.

## Quiz 18 (Input & Output)

1. **Why would you cache a file inside of an operating system even if the process is done using it?**

    The OS should cache files even if a process is done using it because the file may need to be accessed again in the future. For example, the process itself may reopen the file, another process may want the file, the OS may need to interact with the file in some way.

    If the file is cached, it can still be used without having to access the disk which would cause a performance penalty.

2. **What happens if a user process makes an IO requests that can be immediately satisfied by the kernel IO subsystem?**

    If a user process makes an IO requests that can be immediately satisfied by the kernel IO subsystem, the data is transferred (if appropriate) to the process from the kernel IO subsystem, then returns completion or error code. The user process then continues executing with the data provided.

3. **What happens if a user process makes an IO requests that CANNOT be immediately satisfied by the kernel IO subsystem?**

    If a user process makes an IO requests that CANNOT be immediately satisfied by the kernel IO subsystem, the kernel IO subsystem sends a request to the driver. The driver processes the request and commands the controller. The controller then monitors the device, triggering an interrupt when the device completes the operation. The interrupt handler then executes and returns the result to the driver. The driver then triggers the IO subsystem to transfer the data to the user process.

## Quiz 19 (Input, Output, and Distributed Systems)

1. **Why are IO accesses typically computationally expensive?**

    Input and output (IO) accesses are typically computationally expensive because many IO devices are slow (like storage devices), many processes often want to access a single IO device (causing contention), and system calls and interrupts add extra instructions that need to be executed.

    All three of these issues cause IO accesses to be computationally expensive.

2. **Describe at least 1 method for improving IO performance.**

    You can improve IO performance by caching data. If the kernel IO subsystem is capable of supplying IO data without contacting the IO device this makes the IO access non-existent and much faster from the processes perspective.

3. **What does transparency mean when regarding distributed systems? Give an example of a very transparent distributed system and a very opaque distributed system that was not mentioned in lecture.**

    Transparency refers to whether or not the distributed system makes the distributed nature obvious or not.

    A very transparent system is Netflix because you can watch movies and shows that are stored in worldwide data centers from the same interface.

    A very opaque distributed system is World of Warcraft because you have to access a server directly to play your game.

## Quiz 20 (Distributed Systems)

1. **How much down time in seconds does a system with seven 9's of reliability have annually?**

    ```
    365 • 24 60 • 60 = 31,536,000 seconds in a year
    7 9's is 99.99999%
    31,536,000 * (1-0.9999999) = 3.1536 seconds of down time annually
    ```
2. **Resource sharing is an advantage of distributed systems, why is it also a challenge?**
    
    Resource sharing is a challenge because if a resource is scarce many of the computers on the network may want access to it simultaneously.

3. **Why is timing and synchronization a challenge for distributed systems?**
    
    It is not possible to have clocks perfectly synchronized all the time due to time and distance separating many computers that are connected via a network. By the time one computer tries to sync up with another, the time delay may have resulting in further desyncing.
    
    For this reason, it can be very difficult to have all systems agree upon the same time. When there are 1000's of computers on a network, keeping them all synchronized becomes quite difficult.

## Quiz 21 (Networks)

1. **What is the difference between a LAN and a WAN? Give an example of each that we did not discuss in lecture.**
    
    A LAN is a local network, typically covering small distances.
    An example of a LAN is a home network or a small company's network.
    
    A WAN is a wide network, typically covering large distances. An example of a WAN is ATM machine's network or a large company's private global network.

2. **What is a packet? Why don't we just send 1 large packet instead of many small packets?**

    A packet is a chunk of data sent over a network. A single large packet could get lost along the way either entirely or partially. For this reason, many small packets are sent so that if one is lost, only a small portion has to be resent.

3. **What is the network protocol stack? Why is it broken into layers? Isn't 1 layer enough?**

    The network protocol stack defines standards at every level of networking, from user application level, to OS level, to hardware level. One single layer is not enough because at the user application level, you are probably not concerned with the hardware standards, like voltage and frequency. Thus, it is a separate "modular" layer that exists as just a part of the entire communication flow.

## Quiz 22 (Networks)

1. **Which network topologies prevent single points of failure? Why don't we only use these network topologies?**

    The fully connected topology guarantees there is no single point of failure.
    
    This network topology is not used because it is expensive and challenging to connect every node to all other nodes in a network. If a system with 1000 nodes is using the fully connected network topology, that means there are 999 connections on each node.

2. **What is computation migration? Give an example.**

    Computation migration means moving the computation somewhere else. For example, when you ask a question from your phone, your phone does not have 10001s of GPUs connected to it directly. Instead, a data center has all of these GPU's necessary to power which your phone contacts instead. The computation is migrated to the data center, from your phone.

3. **What is process migration? Give an example.**

    Process migration means the process is split into subtasks and migrated to other systems. An example of this is which is where malware infects 1000's of systems and has all of them mine cryptocurrency secretly and the proceeds are sent back to the host. The crytpomining process is split up into subtasks and sent out to all the other systems.

## Quiz 23 (Networks)

1. **In the client/server model, what is the purpose of the server? What is the purpose of the client?**

    The purpose of the server in the client server model is to provide a service that clients can request access to. The purpose of the client in the client server model is to request services from the server.

2. **What is a remote procedure call in the client server model? Why would a remote procedure call ever be necessary?**

    A remote procedure call in the client server model is where you ask the server to execute code on the clients behalf. You would want this because it gives the server the authority over what is executed and the computation is deferred to the server. For example, in a game of tick tack toe, placing Xs and Ois could be something the clients request the server to do on their behalf, then the server can guarantee that no clients are able to make illegal moves.

3. **What is a distributed file system?**

    A distributed file system is when you have files accessed over a network. Typically this involves a file server where many clients connect to to read and write files.