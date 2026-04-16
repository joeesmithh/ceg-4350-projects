# CEG 4350 Practice Final Exam Questions - ANSWERED

## Practice Final Exam 1

1. **It is possible for two different domains to contain the same access rights.**

    ---

   - [x] True
   - [ ] False

    > Note: According to the study guide, a domain is defined as a "set of access-rights." There is no restriction preventing two different domains from having overlapping or identical access rights. For example, two different user groups could both have read access to the same file.

2. **It is uncommon for a DFS to use RPCs.**
    
    ---

    - [ ] True
	- [x] False

    > Note: The study guide explicitly states: "Distributed file systems (DFS) is one of the most common uses of distributed systems and for RPCs." This makes the statement false - it is actually very common for DFS to use RPCs.

3. **The DMA controller and CPU use separate memory busses to communicate with memory to avoid competing for a single bus.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide states: "The DMA controller and CPU are now competing for memory bus time but is still more efficient than requiring the CPU to read individual bytes from the device." They share the same memory bus and compete for access to it.

4. **The star network topology does not have any single points of failure.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide explicitly states about star topology: "If the central node fails, the entire network is lost." The central node is a single point of failure.

5. **In the FAT file system format example we discussed in lecture, sector 25 belongs to what?**

    ---

   - [ ] FAT 2
   - [ ] data area
   - [x] root directory
   - [ ] boot sector
   - [ ] none of these
   - [ ] FAT 1

    > Note: According to the study guide's FAT12 disk organization: Boot sector (sector 0), FAT 1 (sectors 1-9), FAT 2 (sectors 10-18), Root Directory (sectors 19-32), Data Area (sectors 33-n). Sector 25 falls within the root directory range of 19-32.

6. **Which is an example of a WAN?**

    ---

   - [ ] a company's internal network
   - [x] a satellite network
   - [ ] WSU-Secure
   - [ ] the network at your home

    > Note: The study guide defines WAN as connecting "nodes across the state, country, or planet" and lists examples including "satellite channels, cellular networks (4G, 5G, LTE), telephone lines." A satellite network is a WAN. The other options are examples of LANs (Local Area Networks).

7. **Which of the following file allocation methods ensures that all sectors of a file are stored in contiguous sectors.**

    ---

   - [ ] multi-level indexed allocation
   - [ ] none of these
   - [ ] linked allocation
   - [ ] indexed allocation
   - [x] extent-based allocation

    > Note: The study guide describes extent-based allocation as: "the extents or total size of the file are defined ahead of time and this space is allocated to the file (even if not all of it is used)" and lists as a Pro: "Provides simple and fast access to files" which implies contiguous storage. This is the only method that guarantees contiguous sectors.

8. **Which of the following is a piece of software that allows the operating system and IO device to communicate with each other?**

    ---

   - [ ] device controller
   - [x] device driver
   - [ ] device port
   - [ ] system bus

    > Note: The study guide explicitly states: "A driver is a software component that lets the operating system and a device communicate with each other." A device controller is hardware, not software.

9.  **In one or two sentences, explain the role of the virtual file system when using NFS.**

    ---

    ```
    The virtual file system (VFS) provides a standard interface for file access that works for both local and remote file systems, allowing the OS to treat NFS files the same way as local files. The VFS sits above both the local file system modules (like UFS, ext4, APFS) and the NFS module, providing a unified interface regardless of whether files are stored locally or remotely.
    ```

    > Note: From the study guide: "VFS provides a standard interface for file access (regardless if remote or local)" and "NFS module sends and receives RPCs" while "If a read/write request is received on the server, this request is then passed to the local file system module."

10. **In one or two sentences, explain some reasons why most OSs provide a simplified interface for accessing devices rather than having user processes manipulate ports directly.**

    ---

    ```
    OSs provide simplified interfaces for security and access control (to prevent malicious programs from directly manipulating devices), ease of use (devices appear as files in Unix), and to handle buffering, caching, scheduling, and error handling efficiently. Direct port access would require every program to implement these features and could lead to security vulnerabilities and device conflicts.
    ```

    > Note: From the study guide: "Ease of use: On Unix, devices appear as files in the /dev directory", "Access control: The OS must limit how and when devices are accessed to prevent errors or malicious programs", "Buffering and caching: Allows for device data to be efficiently accessible", "Scheduling: If many programs want access to the same device, scheduling access may be necessary", "Error handling and failure recovery."

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
    Free clusters: x0000, x0001, x0004, x0006, x0007 = 5 clusters
    5 clusters × 1 sector/cluster × 512 bytes/sector = 2560 bytes
    ```

    > Note: According to the study guide, FAT entry value 0x0000 indicates the cluster is empty. Counting all entries with 0x0000: indices 0x0000, 0x0001, 0x0004, 0x0006, and 0x0007 gives us 5 free clusters. With 512 bytes per sector and 1 sector per cluster, total free space is 2560 bytes.

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
    File 1: Starting cluster = x0002, Size = 1 cluster = 512 bytes
    File 2: Starting cluster = x0003, Size = 2 clusters = 1024 bytes (chain: x0003 → x0005 → xFFFF)
    File 3: Starting cluster = x0009, Size = 3 clusters = 1536 bytes (chain: x0009 → x000A → x0008 → xFFFF)
    ```

    > Note: According to the study guide, 0xFFFF indicates the end of a file. To find files, we look for chains that end in 0xFFFF. File 1 is a single cluster at 0x0002. File 2 starts at 0x0003 and points to 0x0005 which ends. File 3 starts at 0x0009, points to 0x000A, which points to 0x0008, which ends. Note that 0x0008 appears to be part of the file starting at 0x0009, not a separate file.

## Practice Final Exam 2

1. **On Windows, an access-control list defines what domain can perform what operations for a specific object.**
	
    ---

    - [x] True
	- [ ] False

    > Note: The study guide states: "Access-control list: Each object has a column that defines what domain can perform what operation for that object. Used in Windows and Linux."

2. **In FAT file systems, the inodes on the disk can be placed in any sector on the disk.**

    ---

	- [ ] True
	- [x] False

    > Note: FAT file systems don't use inodes. The study guide describes inodes as part of Unix-like file systems with multi-level indexed allocation. FAT uses the FAT table itself to track file locations, which has a fixed location (sectors 1-18 in the FAT12 example).

3. **PCI is an example of a device port.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide describes PCI as a bus: "Many controllers are all connected to a single bus" in the PCI Bus section. A device port is defined as "the interface which a CPU accesses devices" with types including status, control, data-in, and data-out ports. PCI is a bus, not a port.

4. **It is safer to store a cached copy of a file from a DFS on the disk because it can be recovered in the event of a shutdown.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide states for Local Disk storage: "Advantages: Safer if client fails" and for Local Memory: "Disadvantages: If the client goes down, all progress is lost." This makes disk storage safer for caching.

5. **The FAT filesystem is an example of linked allocation.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide explicitly states: "FAT File System Simplified: Uses linked files where links reside in the File Allocation Table (FAT)." This confirms FAT is a linked allocation method.

6. **It is impossible to have a network topology without a single point of failure.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide describes the fully connected topology: "If one node fails, the other nodes can still communicate with other nodes" - this topology has no single point of failure, proving the statement is false.

7. **Accessing something on a network is always faster than accessing something on a local storage disk.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide states: "Networks are even slower than disks!" This clearly indicates that network access is slower than local disk access, making the statement false.

8. **Ring 5 has more access-rights than ring 0 in the domain implementation of Multics.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide states for Multics domain rings: "The innermost ring has the most amount of privileges" and "The outermost ring has the least amount of privileges." Ring 0 (innermost) has more privileges than ring 5 (outer ring).

9. **On the FAT12 filesystem, the root directory has a fixed size.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide explicitly states: "In FAT16, the root directory is a fixed size in a fixed sector(s)" with "Max size is 4,096 sectors" and "Typical size is 32 sectors." This also applies to FAT12 as described in the lecture notes.

10. **The absolute naming scheme for DFS files is location independent.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide lists as a disadvantage of absolute naming scheme: "File is not location independent." The absolute naming scheme includes the server name in the path (<server name: path name>), making it location-dependent.

11. **Which is an example of a property a stateful DFS server might have?**

    ---

    - [ ] a server that uses RPCs to allow users to access files
    - [ ] a server that treats each request from a client independently
    - [x] a server that tracks who has opened and closed a file to prevent multiple simultaneous accesses
    - [ ] a server that does not have file locks

    > Note: The study guide defines stateful as: "Server maintains information about state of each client's connection or session." Tracking file opens/closes for locking is maintaining state. The study guide also mentions: "In NFSv4, clients can lock file (stateful)." Treating requests independently is stateless, not stateful.

12. **For the FAT12 file system, the boot sector is located in this sector on the disk.**

    ---

    - [x] sector 0
    - [ ] sectors 19-32
    - [ ] sectors 1-9
    - [ ] sector 1

    > Note: The study guide clearly states in the FAT12 disk organization: "Boot Sector (Sector 0)" and "The boot sector is the first sector on the drive."

13. **This network topology is used by ethernet networks**

    ---

    - [ ] ring
    - [ ] ring bus
    - [ ] star
    - [x] linear bus

    > Note: The study guide states about linear bus topology: "Ethernet uses this." Linear bus has a "Single shared link" with "Nodes directly connected to each other."

14. **Which is NOT a method of improving I/O performance?**

    ---

    - [ ] increase RAM
    - [x] disabling DMA
    - [ ] reduce interrupt frequency
    - [ ] using caches

    > Note: The study guide lists methods to improve I/O performance: "Caching", "Reduce interrupt frequency by using larger data transfers", "DMA controllers", "Use multiple IO devices to reduce contention", "Increase RAM to reduce paging." Disabling DMA would worsen performance, not improve it.

15. **This file allocation method uses inodes that identify the starting sector and the sector count of the file.**

    ---

    - [ ] FAT
    - [x] extent-based allocation
    - [ ] indexed allocation
    - [ ] linked allocation

    > Note: The study guide states for extent-based allocation: "Inode contains the location in storage and the size of file." This matches the description of starting sector and sector count.

16. **Given the access matrix:**

    > No image was provided, skip

    **Are there any objects that can be executed by a domain?**

    ---

    - [ ] No, there are no files that can be executed
    - [ ] Yes, all files can be executed by an admin
    - [ ] Yes, F3 can be executed by user in D3
    - [ ] Yes, D3 can be executed by user in F3

    > Note: Without the access matrix image, cannot determine the correct answer. Based on typical access matrix structure, the most likely answer would be the option that correctly identifies an object (file) that can be executed by a domain (user/process), which would be option 3 (F3 can be executed by user in D3) as domains execute objects, not the other way around.

17. **If a user processes makes an I/O system call and the kernel I/O subsystem can already satisfy the request, the next step the kernel I/O subsystem performs is**

    ---

    - [x] transfers data to process
    - [ ] send a request to the device driver, blocking the process
    - [ ] interrupt the user process when the I/O has completed
    - [ ] issue commands to the device controller

    > Note: The study guide states in "OS Processing a Read Call": "The OS checks if the data exists inside a cache" and if it does exist, it would transfer the data directly to the process without needing to go through the device driver. The diagram shows "transfer data (if appropriate) to process, return completion or error code" as the direct path when data is already in cache.

18. **The device controller receives commands from the device driver and then based on these commands**

    ---

    - [ ] controls the kernel I/O subsystem
    - [x] controls the device itself
    - [ ] controls the OS
    - [ ] controls the driver

    > Note: The study guide defines controller as: "a piece of hardware that receives data over the system bus and translates them into actions performed by the device." The controller's job is to control the actual device based on driver commands.

19. **This layer of the ISO network protocol stack is provided by the OS itself.**

    ---

    - [ ] application layer
    - [ ] physical layer
    - [x] transport layer
    - [ ] session layer

    > Note: The study guide states: "Transport layer: reliable end-to-end communication between any set of nodes. Provided by OS." The application layer is provided by user applications, session layer by libraries, and physical layer by hardware.

20. **A write through cache for a client connected to a DFS does NOT have any added benefit by using a cache compared to the remote access model for**

    ---

    - [ ] crashes or failures
    - [x] cache writes
    - [ ] cache reads and writes
    - [ ] cache reads

    > Note: The study guide states about write through: "This method is equivalent to the remote access model for writes, only exploits caching for reads." This means write through provides no benefit for writes compared to remote access, but does benefit reads.

21. **Write a single line of code that will load the entire boot sector from disk 0 into memory from addresses 0x40000 to 0x401FF.**

    **(Assume you are using the functions provided by fdc.c provided in the project sample code and assume you are using a FAT12 file system.)**

    ---

    ```c
    fdc_read(0, 0, 1, 1, (char*)0x40000);
    ```

    > Note: Based on typical floppy disk controller (fdc) function signatures from OS projects, the function would be fdc_read(cylinder, head, sector, count, buffer). For FAT12, the boot sector is at CHS (0, 0, 1) - cylinder 0, head 0, sector 1 (sectors start at 1, not 0 in CHS addressing). We need to read 1 sector (512 bytes) into the buffer at address 0x40000. The boot sector is 512 bytes (0x40000 to 0x401FF is 512 bytes = 0x200 in hex).

22. **Calculate the access time for 5 sectors and 500 sectors on a storage drive with the following parameters:**
    
    **Seek Time = 4ms**
    
    **Rotational Delay = 5ms**
    
    **Throughput = 200 MB/s**

    **Write your times for 5 sector and 500 sector access times rounded to the nearest millisecond (ms):**

    ---

    ```
    Formula: access time = seek time + rotational delay + (# bytes / throughput)
    
    For 5 sectors (5 × 512 bytes = 2,560 bytes):
    access time = 4ms + 5ms + (2,560 bytes / 200 MB/s)
    access time = 4ms + 5ms + (2,560 / 200,000,000 bytes/s × 1000 ms/s)
    access time = 4ms + 5ms + 0.0128ms
    access time = 9.0128ms ≈ 9ms
    
    For 500 sectors (500 × 512 bytes = 256,000 bytes):
    access time = 4ms + 5ms + (256,000 bytes / 200 MB/s)
    access time = 4ms + 5ms + (256,000 / 200,000,000 bytes/s × 1000 ms/s)
    access time = 4ms + 5ms + 1.28ms
    access time = 10.28ms ≈ 10ms
    ```

    > Note: From the study guide: "access time = seek time + rotational delay + # bytes / disk throughput". We convert 200 MB/s to bytes/second: 200 MB/s = 200,000,000 bytes/second. Each sector is 512 bytes. The access time is dominated by seek time and rotational delay (9ms total), with relatively small data transfer time even for 500 sectors (only adds 1.28ms).

23. **Explain in one or two sentences who is correct and why, Sophie or Jack?**

    **Jack says that he is going to format his brand new 1 TB hard drive using the FAT12 file system.**

    **Sophie suggests that the FAT12 file system cannot utilize the entire 1 TB of hard drive space and that this is a bad idea.**

    **Jack argues that he can always make the FAT tables bigger so that he can allocate data to more sectors on the disk and fully utilize the 1 TB hard drive using FAT12.**

    ---

    ```
    Sophie is correct. FAT12 uses 12-bit entries, which means it can only address a maximum of 2^12 = 4,096 clusters, and even with the maximum cluster size, FAT12 is fundamentally limited by its 12-bit addressing to a maximum of around 32 MB. Making the FAT tables bigger doesn't help because the limitation is in the 12-bit entry size itself, not the table size - you would need FAT16 or FAT32 for larger drives.
    ```

    > Note: The "12" in FAT12 refers to the fact that each FAT entry is 12 bits. With 12 bits, you can only represent 2^12 = 4,096 different values (clusters 0-4095, though some are reserved). Even at maximum cluster size, this severely limits total capacity. The study guide mentions "FAT16: 2 GB (65,536 clusters × 32 KB cluster size)" and "FAT32: 8.5 TB (268,435,455 clusters × 32 KB cluster size)" as max sizes, implying FAT12 is much smaller. Jack's argument fails because making the table bigger doesn't change the fundamental 12-bit limitation of each entry - you can't address more than 4,096 clusters regardless of table size.

24. **In one to two sentences, describe what a file system is and why we need a file system.**

    ---

    ```
    A file system is a method of organizing and storing files on storage devices, keeping files organized and accessible through directories and metadata structures that map human-readable names to physical storage locations. We need file systems to provide persistence (keeping files forever unless deleted), ease of use (human-readable names instead of raw sectors), speed and efficiency (quickly accessing any file), and protection (preventing unauthorized access and file corruption).
    ```

    > Note: From the study guide: "A file system keeps our files in storage organized and accessible" and the goals of a file system include "Persistence: Keep files forever (unless we delete them)", "Ease of use: Give human readable names to files and directories", "Speed and efficiency: Quickly access any file", and "Protection: Protect files from other files and prevent unauthorized access."

## Practice Final Exam 3

1. **The ISO network protocol has 7 layers.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide lists the 7 ISO network protocol stack layers: Application, Presentation, Session, Transport, Network, Data Link Control, and Physical.

2. **The client-server model differs from the peer-to-peer model.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide mentions: "This differs from the Peer-to-Peer model" when describing client/server model, indicating they are different paradigms.

3. **In FAT12, a files filename is stored inside of its first logical cluster.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide states that in the directory format, each 32-byte directory entry contains the filename (8 bytes) and extension (3 bytes), along with the First Logical Cluster pointer. The filename is stored in the directory entry, not in the file's data cluster.

4. **A stateless DFS is less complex than a stateful DFS.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide states for stateless: "Less complex than stateful" and for stateful: "More complexity, especially with replicated server instances."

5. **Write-back caching for a DFS client can reduce network traffic if the same block is written to multiple times.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide explicitly states for write-back: "Reduces network traffic if the same block of a file is written to multiple times" because changes are only sent to the server when the file is closed, not on every write.

6. **When moving a process into memory using static relocation, the process cannot be moved after it has been assigned to memory.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide states for static relocation: "Once the process is assigned to memory it cannot be moved" because "Moving would require re-offsetting all the addresses for every instruction in the program!"

7. **The interrupt vector table contains addresses for hardware interrupt routines but not for software interrupt routines.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide states: "The interrupt vector table provides addresses for routines that get executed when interrupts occur" and includes both "Software interrupts (TRAPs and exceptions)" and "Hardware interrupts."

8. **IO accesses are not computationally expensive.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide explicitly states: "IO accesses are computationally expensive" and lists reasons including "Most IO devices are slow", "Contention from multiple processes", and "IO is typically handled through system calls and interrupt handling which adds extra time."

9. **In UNIX-like OSs it is not possible to execute a file that a different user in a different domain has created.**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide mentions the setuid bit: "Files may have a setuid bit in metadata, which allows the process to execute within the domain of the user that created the file instead." This shows it IS possible to execute files created by other users, making the statement false.

10. **MS-DOS was written in assembly which prevented it from running on any processor other than 8088.**

    ---
	
    - [x] True
	- [ ] False

    > Note: The study guide states: "Assembly language is unique to the CPU's architecture. If you write assembly language to run on x86 it will NEVER run on ARM" and gives the example: "MS-DOS was written in 8088 assembly, and is only available on Intel family of CPUs."

11. **On Unix-like OSs, IO devices appear**

    ---

    - [ ] as a port
    - [x] as files in the /dev directory
    - [ ] at the mount point
    - [ ] as programs that can be executed

    > Note: The study guide explicitly states: "Ease of use: On Unix, devices appear as files in the /dev directory."

12. **In the mount point naming scheme**

    ---

    - [ ] remote path cannot be mounted to different local paths for multiple clients 
    - [ ] a file always has the same name for different clients
    - [ ] directories are mapped independently for each file, not at boot time 
    - [x] a file can have different names for different clients

    > Note: The study guide lists as a disadvantage of mount point naming: "Same file can have multiple names (remote path can be mounted to different local paths for multiple clients)."

13. **Which is a good example a feature of a stateful server?**

    ---

    - [x] tracking which remote files are being accessed by what clients
    - [ ] having a distributed file system that can send files to clients
    - [ ] communicating with clients via remote procedure calls
    - [ ] storing of all of the files that currently exist on the file system

    > Note: The study guide defines stateful as: "Server maintains information about state of each client's connection or session." Tracking which clients are accessing which files is maintaining client state. The other options could apply to both stateful and stateless servers.

14. **Typically, there are this many bytes in a sector**

    ---

    - [ ] 1
    - [x] 512
    - [ ] 80
    - [ ] 64

    > Note: The study guide states: "A sector typically consists of 512 bytes."

15. **In FAT12, to find the end of a file you must look for a FAT entry that is the hex value**

    ---

    - [ ] 0x000
    - [ ] 0xFF7
    - [x] 0xFFF
    - [ ] EOF

    > Note: The study guide states: "In FAT16, every 16-bits either... Indicates the cluster is the last cluster of a file (0xFFFF)." For FAT12 (12-bit entries), this would be 0xFFF (the maximum 12-bit value).

16. **In the domain ring implementation of object protection**

    ---

    - [ ] ring 1 has less privileges than ring 2
    - [x] inner rings have all the privileges of outer rings
    - [ ] ring n-1 has more privileges than the inner rings
    - [ ] ring 0 has the fewest privileges 

    > Note: The study guide states: "The innermost ring has the most amount of privileges" and "If Di and Dj are two domains in the domain ring, and j < i, then Di is a subset of Dj. Simply put, the innermost ring has all of the privileges surrounding it."

17. **A process in this state is waiting for something to happen before it can run again**

    ---

    - [ ] running
    - [ ] yield
    - [ ] ready
    - [x] waiting

    > Note: The study guide defines the waiting state: "The process cannot run because it is waiting for something to happen."

18. **When there is memory space in between processes that is too small to be utilized it is called**

    ---

    - [ ] internal fragmentation
    - [ ] compaction
    - [ ] page fault
    - [x] external fragmentation

    > Note: The study guide defines external fragmentation as: "The memory between processes that is too small to be used."

19. **Which is not an advantage to distributed systems?**

    ---

    - [ ] reliability
    - [ ] resource sharing
    - [ ] computation speedup
    - [x] shared memory

    > Note: The study guide lists advantages of distributed systems as: "Resource sharing", "Computation speedup", "Reliability", and "Communication." Shared memory is actually a feature of parallel systems (tightly coupled), not distributed systems where "Each processor has its own clock, memory, and OS."

20. **This file allocation method guarantees files are stored in contiguous sectors.**

    ---

    - [ ] indexed allocation
    - [ ] multi-level indexed allocation
    - [ ] linked allocation
    - [x] extent-based allocation

    > Note: The study guide describes extent-based allocation as defining "the extents or total size of the file... ahead of time and this space is allocated to the file," which implies contiguous allocation. This is the only method that guarantees contiguity.

21. **In 1 or 2 sentences, describe the difference between data migration, computation migration, and process migration for distributed systems.**

    ---

    ```
    Data migration involves moving data between systems (like file transfers or emails), computation migration moves the data to where the computation happens (like search engines processing queries on their servers), and process migration moves both the process and its data to another system (like SETI@home distributing computation to user processors). Each represents a different tradeoff between what is moved versus where the work is performed.
    ```

    > Note: From the study guide: "Data Migration: Moving data between systems - Email, messages, file transfers"; "Computation Migration: Move the data to a computation - Search engines take your query, compute, and provide results"; "Process Migration: Move the process (computation and data) or part of a process - SETI@home uses your processor for compute, then sends results back to a server."

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
    x0005 → x0004 → x0003 → x0007 → xFFFF
    Clusters in order: x0005, x0004, x0003, x0007
    ```

    > Note: Following the FAT chain starting at x0005: x0005 points to x0004, x0004 points to x0003, x0003 points to x0007, x0007 contains xFFFF (end of file). The clusters that make up this file in order are: x0005, x0004, x0003, x0007.

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
    File 1: Starting cluster = x0005, Cluster count = 4 (chain: x0005 → x0004 → x0003 → x0007)
    File 2: Starting cluster = x0006, Cluster count = 2 (chain: x0006 → x0002)
    File 3: Starting cluster = x0008, Cluster count = 1 (chain: x0008 → xFFFF)
    ```

    > Note: To find starting clusters, we need to identify clusters that are not pointed to by any other cluster. x0002, x0003, x0004, and x0007 are all pointed to by other clusters, so they cannot be starting clusters. x0005, x0006, and x0008 are never pointed to, making them starting clusters. Following each chain to xFFFF gives us the cluster counts.

24. **In 1 or 2 sentences, describe the relationship between device drivers, device controllers, and the devices themselves.**

    ---

    ```
    Device drivers are software components that translate OS commands into device-specific instructions and send them to device controllers. Device controllers are hardware components that receive commands from drivers via the system bus and translate them into physical actions performed by the actual device (like reading a disk or displaying on a monitor).
    ```

    > Note: From the study guide: "A driver is a software component that lets the operating system and a device communicate with each other"; "Controller: a piece of hardware that receives data over the system bus and translates them into actions performed by the device."

## Practice Final Exam 4

1. **In the FAT12 file system, a file's filename is stored inside of the first 8 bytes of its respective directory entry.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide shows the directory entry format with "Filename (8 bytes)" as the first field in the 32-byte directory entry structure.

2. **In preemptive multitasking, a process must willingly yield or give up control for another task to run**

    ---

	- [ ] True
	- [x] False

    > Note: The study guide defines preemptive multitasking as: "A process can be preempted by the OS" using "Periodic timers interrupt the process" and "Device interrupts." The description of "must willingly yield" describes cooperative multitasking, not preemptive. In preemptive multitasking, the OS forcibly interrupts processes.

3. **For a distributed file system, location transparency means the name of the file does not reveal the physical storage location**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide defines location transparency: "The name of the file does not reveal the physical storage location" with Amazon S3 as an example where "Users interact with S3 through a simple API or a web interface without needing to know the physical location of their stored objects."

4. **The interrupt vector table provides addresses for routines that get executed when interrupts occur.**

    ---

	- [x] True
	- [ ] False

    > Note: The study guide explicitly states: "The interrupt vector table provides addresses for routines that get executed when interrupts occur."

5. **Which of the following is NOT a preemptive scheduling algorithm?**

    ---

   - [ ] SRTF
   - [ ] Round Robin
   - [ ] MLFQ
   - [x] FIFO

    > Note: The study guide states for FIFO: "This method is cooperative (requires process to release the CPU)" and for Round Robin: "This method is preemptive (uses a clock to force processes to stop)." FIFO is cooperative/non-preemptive, while SRTF, RR, and MLFQ are all preemptive.

6. **What is an advantage to dynamic relocation that uses a base and limit register without paging?**

    ---

   - [ ] less hardware decreases time to access memory
   - [ ] sharing memory between processes is possible
   - [ ] a process' memory is contiguous
   - [x] can allow a process to grow over time

    > Note: The study guide lists advantages of dynamic relocation: "OS can move a process in memory much easier" and "OS can allow a process to grow over time." The disadvantages include "Extra hardware may increase time to access memory" and "Sharing memory between processes is impossible."

7. **Which type of device port indicates if a device is busy, ready, or has an error?**

    ---

   - [ ] data-in port
   - [ ] data-out port
   - [ ] control port
   - [x] status port

    > Note: The study guide defines the 4 types of ports: "Status port: indicates if a device is busy, ready, or has an error."

8. **Which file allocation method guarantees file blocks are stored sequentially on storage?**

    ---

   - [ ] linked allocation
   - [x] extent-based allocation
   - [ ] multi-level indexed allocation
   - [ ] indexed allocation

    > Note: Extent-based allocation allocates contiguous space for files ahead of time, guaranteeing sequential/contiguous storage. The study guide describes it as allocating "the extents or total size of the file... ahead of time and this space is allocated to the file."

9. **In one or two sentences, how many files are there in the file system given the following FAT table. Explain your reasoning.**

    ```
    00000200 00 00 00 00 03 00 ff ff ff ff 06 00 07 00 ff ff
    00000210 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    ```

    ---

    ```
    There are 2 files in the file system. Looking at the FAT entries (in little-endian 16-bit format): entry at index 2 contains 0x0003 (points to cluster 3), entry at index 3 contains 0xFFFF (end of file 1), entry at index 5 contains 0x0006, entry at index 6 contains 0x0007, and entry at index 7 contains 0xFFFF (end of file 2).
    ```

    > Note: Reading the hex dump as 16-bit FAT16 entries in little-endian format: bytes "00 00" = 0x0000 (free), "00 00" = 0x0000 (free), "03 00" = 0x0003, "ff ff" = 0xFFFF (EOF), "ff ff" = 0xFFFF (this would be entry 3, already counted), "06 00" = 0x0006, "07 00" = 0x0007, "ff ff" = 0xFFFF. File 1 is at cluster 2→3 (ends at 3), File 2 is at cluster 5→6→7 (ends at 7).

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
    Name: "file b  ", Extension: "txt", Starting physical sector: 38
    
    Reasoning: The root directory entries show three files. "file a" starts at cluster 0x0002 (2 clusters), "file b" starts at cluster 0x0005 (3 clusters: 5→6→7), and "file c" starts at cluster 0x0004 (1 cluster). File b is the largest with 3 clusters. Assuming FAT12 layout with data area starting at sector 33, cluster 5 maps to sector 33 + (5-2) = sector 38.
    ```

    > Note: Reading the directory entries: First 8 bytes are filename ("file a  ", "file b  ", "file c  "), next 3 bytes are extension ("txt"), and at offset 26-27 is the first logical cluster (0x0002, 0x0005, 0x0004). From the FAT, file b (starting at cluster 5) has 3 clusters (5→6→7→EOF), making it the largest. In FAT12, clusters 2+ start at sector 33, so cluster 5 is at sector 33 + (5-2) = sector 38.

11. **In one or two sentences, explain what a remote procedure call is and what they are used for.**

    ---

    ```
    A remote procedure call (RPC) is a way of requesting a server to execute a procedure or function on the client's behalf, where the client calls the server's procedures and receives results as if they were local function calls. RPCs are commonly used in client/server systems, distributed file systems like NFS, and applications like online gaming to allow clients to request services from remote servers.
    ```

    > Note: From the study guide: "A remote procedure call is a way of requesting a server to execute a procedure or function on the client's behalf" and "RPCs are very common in many types of client/server systems."

12. **In one or two sentences, explain why the keyboard sends "scancodes" instead of ASCII characters.**

    ---

    ```
    Keyboards send scancodes instead of ASCII because scancodes can represent all keys including special keys that have no ASCII equivalent (like SHIFT, CTRL, INSERT, function keys), and scancodes allow support for different keyboard layouts (US English, UK English, Chinese, Spanish, etc.) by letting the OS translate the scancode based on the configured keyboard type.
    ```

    > Note: From the study guide: "There are many different types of keyboards (US English, UK (British) English, Chinese, Spanish, etc.). To ensure support for these keyboards, scancodes are used (not ASCII)" and "There is no ASCII equivalent for special keys like SHIFT or INSERT so scancodes must be used to register all the keys."
