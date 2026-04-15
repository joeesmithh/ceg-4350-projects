# CEG 4350 Practice Final Exam Questions

## Practice Final Exam 1

1. **It is possible for two different domains to contain the same access rights.**

    ---

   - [ ] True
   - [ ] False

    > Note: 

2. **It is uncommon for a DFS to use RPCs.**
    
    ---

    - [ ] True
	- [ ] False

    > Note: 

3. **The DMA controller and CPU use separate memory busses to communicate with memory to avoid competing for a single bus.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

4. **The star network topology does not have any single points of failure.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

5. **In the FAT file system format example we discussed in lecture, sector 25 belongs to what?**

    ---

   - [ ] FAT 2
   - [ ] data area
   - [ ] root directory
   - [ ] boot sector
   - [ ] none of these
   - [ ] FAT 1

    > Note: 

6. **Which is an example of a WAN?**

    ---

   - [ ] a company's internal network
   - [ ] a satellite network
   - [ ] WSU-Secure
   - [ ] the network at your home

    > Note: 

7. **Which of the following file allocation methods ensures that all sectors of a file are stored in contiguous sectors.**

    ---

   - [ ] multi-level indexed allocation
   - [ ] none of these
   - [ ] linked allocation
   - [ ] indexed allocation
   - [ ] extent-based allocation

    > Note: 

8. **Which of the following is a piece of software that allows the operating system and IO device to communicate with each other?**

    ---

   - [ ] device controller
   - [ ] device driver
   - [ ] device port
   - [ ] system bus

    > Note: 

9.  **In one or two sentences, explain the role of the virtual file system when using NFS.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

10. **In one or two sentences, explain some reasons why most OSs provide a simplified interface for accessing devices rather than having user processes manipulate ports directly.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

11. **Given the following FAT:**

    | Index | Entry |
    | ----- | ----- |
    | x0000 | x0000 |
    | x0001 | x0000 |
    | x0002 | xFFFF |
    | x0003 | x0005 |
    | x0004 | x0000 |
    | x0005 | xFFFF |
    | x0006 | x0000 |
    | x0007 | x0000 |
    | x0008 | xFFFF |
    | x0009 | x000A |
    | x000A | x0008 |

    **Calculate the amount of free space on the drive in bytes.**

    **Assume that each cluster contains 1 sector.**

    **Assume that each sector contains 512 bytes.**

    **Assume that the provided FAT describes the entire drive.**

    ---

    ```
    Your calculation here...
    ```

    > Note: 

12. **Given the following FAT:**

    | Index | Entry |
    | ----- | ----- |
    | x0000 | x0000 |
    | x0001 | x0000 |
    | x0002 | xFFFF |
    | x0003 | x0005 |
    | x0004 | x0000 |
    | x0005 | xFFFF |
    | x0006 | x0000 |
    | x0007 | x0000 |
    | x0008 | xFFFF |
    | x0009 | x000A |
    | x000A | x0008 |

    **List each file's starting cluster and the amount of space in bytes each file occupies in bytes.**

    **Assume that each cluster contains 1 sector.**

    **Assume that each sector contains 512 bytes.**

    **Assume that the provided FAT describes the entire drive.**

    ---

    ```
    Your calculation here...
    ```

    > Note: 

## Practice Final Exam 2

1. **On Windows, an access-control list defines what domain can perform what operations for a specific object.**
	
    ---

    - [ ] True
	- [ ] False

    > Note: 

2. **In FAT file systems, the inodes on the disk can be placed in any sector on the disk.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

3. **PCI is an example of a device port.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

4. **It is safer to store a cached copy of a file from a DFS on the disk because it can be recovered in the event of a shutdown.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

5. **The FAT filesystem is an example of linked allocation.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

6. **It is impossible to have a network topology without a single point of failure.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

7. **Accessing something on a network is always faster than accessing something on a local storage disk.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

8. **Ring 5 has more access-rights than ring 0 in the domain implementation of Multics.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

9. **On the FAT12 filesystem, the root directory has a fixed size.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

10. **The absolute naming scheme for DFS files is location independent.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

11. **Which is an example of a property a stateful DFS server might have?**

    ---

    - [ ] a server that uses RPCs to allow users to access files
    - [ ] a server that treats each request from a client independently
    - [ ] a server that tracks who has opened and closed a file to prevent multiple simultaneous accesses
    - [ ] a server that does not have file locks

    > Note: 

12. **For the FAT12 file system, the boot sector is located in this sector on the disk.**

    ---

    - [ ] sector 0
    - [ ] sectors 19-32
    - [ ] sectors 1-9
    - [ ] sector 1

    > Note: 

13. **This network topology is used by ethernet networks**

    ---

    - [ ] ring
    - [ ] ring bus
    - [ ] star
    - [ ] linear bus

    > Note: 

14. **Which is NOT a method of improving I/O performance?**

    ---

    - [ ] increase RAM
    - [ ] disabling DMA
    - [ ] reduce interrupt frequency
    - [ ] using caches

    > Note: 

15. **This file allocation method uses inodes that identify the starting sector and the sector count of the file.**

    ---

    - [ ] FAT
    - [ ] extent-based allocation
    - [ ] indexed allocation
    - [ ] linked allocation

    > Note: 

16. **Given the access matrix:**

    > No image was povided, skip

    **Are there any objects that can be executed by a domain?**

    ---

    - [ ] No, there are no files that can be executed
    - [ ] Yes, all files can be executed by an admin
    - [ ] Yes, F3 can be executed by user in D3
    - [ ] Yes, D3 can be executed by user in F3

    > Note: 

17. **If a user processes makes an I/O system call and the kernel I/O subsystem can already satisfy the request, the next step the kernel I/O subsystem performs is**

    ---

    - [ ] transfers data to process
    - [ ] send a request to the device driver, blocking the process
    - [ ] interrupt the user process when the I/O has completed
    - [ ] issue commands to the device controller

    > Note: 

18. **The device controller receives commands from the device driver and then based on these commands**

    ---

    - [ ] controls the kernel I/O subsystem
    - [ ] controls the device itself
    - [ ] controls the OS
    - [ ] controls the driver

    > Note: 

19. **This layer of the ISO network protocol stack is provided by the OS itself.**

    ---

    - [ ] application layer
    - [ ] physical layer
    - [ ] transport layer
    - [ ] session layer

    > Note: 

20. **A write through cache for a client connected to a DFS does NOT have any added benefit by using a cache compared to the remote access model for**

    ---

    - [ ] crashes or failures
    - [ ] cache writes
    - [ ] cache reads and writes
    - [ ] cache reads

    > Note: 

21. **Write a single line of code that will load the entire boot sector from disk 0 into memory from addresses 0x40000 to 0x401FF.**

    **(Assume you are using the functions provided by fdc.c provided in the project sample code and assume you are using a FAT12 file system.)**

    ---

    ```c
    // Your code here...
    ```

    > Note: 

22. **Calculate the access time for 5 sectors and 500 sectors on a storage drive with the following parameters:**
    
    **Seek Time = 4ms**
    
    **Rotational Delay = 5ms**
    
    **Throughput = 200 MB/s**

    **Write your times for 5 sector and 500 sector access times rounded to the nearest millisecond (ms):**

    ---

    ```
    Your calculation here...
    ```

    > Note: 

23. **Explain in one or two sentences who is correct and why, Sophie or Jack?**

    **Jack says that he is going to format his brand new 1 TB hard drive using the FAT12 file system.**

    **Sophie suggests that the FAT12 file system cannot utilize the entire 1 TB of hard drive space and that this is a bad idea.**

    **Jack argues that he can always make the FAT tables bigger so that he can allocate data to more sectors on the disk and fully utilize the 1 TB hard drive using FAT12.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

24. **In one to two sentences, describe what a file system is and why we need a file system.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

## Practice Final Exam 3

1. **Typically, all sectors in a file tend to be accessed together and sequentially.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

2. **In the FAT12 file system, sector 8 is a part of a copy the FAT table.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

3. **Parallel systems have less frequent communications and communicate over a network instead of a system bus.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

4. **When using client-initiated consistency with the caching model, the file server detects potential conflicts and invalidates caches.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

5. **A filesystem implemented with FAT12 can check to see if a directory entry is empty by simply checking if the first character of the filename is null.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

6. **When moving a process into memory using static relocation, the process cannot be moved after it has been assigned to memory.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

7. **The interrupt vector table contains addresses for hardware interrupt routines but not for software interrupt routines.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

8. **IO accesses are not computationally expensive.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

9. **In UNIX-like OSs it is not possible to execute a file that a different user in a different domain has created.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

10. **MS-DOS was written in assembly which prevented it from running on any processor other than 8088.**

    ---
	
    - [ ] True
	- [ ] False

    > Note: 

11. **On Unix-like OSs, IO devices appear**

    ---

    - [ ] as a port
    - [ ] as files in the /dev directory
    - [ ] at the mount point
    - [ ] as programs that can be executed

    > Note: 

12. **In the mount point naming scheme**

    ---

    - [ ] remote path cannot be mounted to different local paths for multiple clients 
    - [ ] a file always has the same name for different clients
    - [ ] directories are mapped independently for each file, not at boot time 
    - [ ] a file can have different names for different clients

    > Note: 

13. **Which is a good example a feature of a stateful server?**

    ---

    - [ ] tracking which remote files are being accessed by what clients
    - [ ] having a distributed file system that can send files to clients
    - [ ] communicating with clients via remote procedure calls
    - [ ] storing of all of the files that currently exist on the file system

    > Note: 

14. **Typically, there are this many bytes in a sector**

    ---

    - [ ] 1
    - [ ] 512
    - [ ] 80
    - [ ] 64

    > Note: 

15. **In FAT12, to find the end of a file you must look for a FAT entry that is the hex value**

    ---

    - [ ] 0x000
    - [ ] 0xFF7
    - [ ] 0xFFF
    - [ ] EOF

    > Note: 

16. **In the domain ring implementation of object protection**

    ---

    - [ ] ring 1 has less privileges than ring 2
    - [ ] inner rings have all the privileges of outer rings
    - [ ] ring n-1 has more privileges than the inner rings
    - [ ] ring 0 has the fewest privileges 

    > Note: 

17. **A process in this state is waiting for something to happen before it can run again**

    ---

    - [ ] running
    - [ ] yield
    - [ ] ready
    - [ ] waiting

    > Note: 

18. **When there is memory space in between processes that is too small to be utilized it is called**

    ---

    - [ ] internal fragmentation
    - [ ] compaction
    - [ ] page fault
    - [ ] external fragmentation

    > Note: 

19. **Which is not an advantage to distributed systems?**

    ---

    - [ ] reliability
    - [ ] resource sharing
    - [ ] computation speedup
    - [ ] shared memory

    > Note: 

20. **This file allocation method guarantees files are stored in contiguous sectors.**

    ---

    - [ ] indexed allocation
    - [ ] multi-level indexed allocation
    - [ ] linked allocation
    - [ ] extent-based allocation

    > Note: 

21. **In 1 or 2 sentences, describe the difference between data migration, computation migration, and process migration for distributed systems.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

22. **Given the following FAT:**

    | Index | Entry |
    | ----- | ----- |
    | x0002 | xFFFF |
    | x0003 | x0007 |
    | x0004 | x0003 |
    | x0005 | x0004 |
    | x0006 | x0002 |
    | x0007 | xFFFF |
    | x0008 | xFFFF |

    **List all the clusters in order that make up the file stored at cluster x0005.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

23. **Given the following FAT:**

    | Index | Entry |
    | ----- | ----- |
    | x0002 | xFFFF |
    | x0003 | x0007 |
    | x0004 | x0003 |
    | x0005 | x0004 |
    | x0006 | x0002 |
    | x0007 | xFFFF |
    | x0008 | xFFFF |
    
    **List all of the starting clusters of each file in the FAT and the cluster count for each file.**

    **Assume that files cannot share clusters with each other.**

    **Assume these are the only filled entries of the FAT.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

24. **In 1 or 2 sentences, describe the relationship between device drivers, device controllers, and the devices themselves.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

## Practice Final Exam 4

1. **In the FAT12 file system, a file's filename is stored inside of the first 8 bytes of its respective directory entry.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

2. **In preemptive multitasking, a process must willingly yield or give up control for another task to run**

    ---

	- [ ] True
	- [ ] False

    > Note: 

3. **For a distributed file system, location transparency means the name of the file does not reveal the physical storage location**

    ---

	- [ ] True
	- [ ] False

    > Note: 

4. **The interrupt vector table provides addresses for routines that get executed when interrupts occur.**

    ---

	- [ ] True
	- [ ] False

    > Note: 

5. **Which of the following is NOT a preemptive scheduling algorithm?**

    ---

   - [ ] SRTF
   - [ ] Round Robin
   - [ ] MLFQ
   - [ ] FIFO

    > Note: 

6. **What is an advantage to dynamic relocation that uses a base and limit register without paging?**

    ---

   - [ ] less hardware decreases time to access memory
   - [ ] sharing memory between processes is possible
   - [ ] a process' memory is contiguous
   - [ ] can allow a process to grow over time

    > Note: 

7. **Which type of device port indicates if a device is busy, ready, or has an error?**

    ---

   - [ ] data-in port
   - [ ] data-out port
   - [ ] control port
   - [ ] status port

    > Note: 

8. **Which file allocation method guarantees file blocks are stored sequentially on storage?**

    ---

   - [ ] linked allocation
   - [ ] extent-based allocation
   - [ ] multi-level indexed allocation
   - [ ] indexed allocation

    > Note: 

9. **In one or two sentences, how many files are there in the file system given the following FAT table. Explain your reasoning.**

    ```
    00000200 00 00 00 00 03 00 ff ff ff ff 06 00 07 00 ff ff
    00000210 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    ```

    ---

    ```
    Your answer here...
    ```

    > Note: 

10. **In one or two sentences, what is the name, extension, and starting physical sector (not file cluster) of the largest file on the file system given the following FAT table and root directory. Explain your reasoning.**

    **Table:**

    ```
    00000200 00 00 00 00 03 00 ff ff ff ff 06 00 07 00 ff ff
    00000210 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    ```

    **Root Directory**

    ```
    00002600 66 69 6c 65 20 61 20 20 74 78 74 00 00 00 00 00
    00002610 00 00 00 00 00 00 00 00 00 00 02 00 00 04 00 00
    00002620 66 69 6c 65 20 62 20 20 74 78 74 00 00 00 00 00
    00002630 00 00 00 00 00 00 00 00 00 00 05 00 00 06 00 00
    00002640 66 69 6c 65 20 63 20 20 74 78 74 00 00 00 00 00
    00002650 00 00 00 00 00 00 00 00 00 00 04 00 00 02 00 00
    ```

    ---

    ```
    Your answer here...
    ```

    > Note: 

11. **In one or two sentences, explain what a remote procedure call is and what they are used for.**

    ---

    ```
    Your answer here...
    ```

    > Note: 

12. **In one or two sentences, explain why the keyboard sends "scancodes" instead of ASCII characters.**

    ---

    ```
    Your answer here...
    ```

    > Note: 
