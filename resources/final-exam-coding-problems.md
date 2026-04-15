# CEG 4350 Practice Final Exam Coding Problems

## Question 1

**In C, write a function called int ``countFiles()`` that will count the number of files in the currently opened directory `(directory_t currentDirectory)` and return the count. Next, write another function called int `countSubdirectories()` that will count the number of subdirectories in the currently opened directory and return the count.**

**When counting subdirectories, ensure that you do not include the self directory entry `(./)` or the parent directory entry `(../)` in the count.**

**(Assume you have all functions provided to you in the sample code provided for your OS.)**

**(You may not use any functions that you did not write or that were not included with the sample code. i.e. you cannot use stdio.h and stdlib.h)**

---

```c
// Your code here
```

## Question 2

**In C, write a function called `int renameSubdirectory(char *currentName, char *newName)` that will rename the subdirectory with the current name `(char *currentName)` in the current directory `(directory_t currentDirectory)` with the new name `(char *newName)`.**

**You must modify the current directory to properly change the subdirectory name. Once the current directory is modified, write the changes back to the floppy disk using `floppy_write()` inside of the `renameSubdirectory` function. The writing of these changes should work for both the root directory and subdirectories.**

**Perform error handling where necessary:**

- **If the `newName`'s length is not between 1 and 8, do not save any changes to disk, return non-zero.**
- **If the subdirectory cannot be found, return non-zero.**
- **If any `floppy_write()` fails, return non-zero.**

**(Assume you have all functions provided to you in the sample code provided for your OS.)**

**(You may not use any functions that you did not write or that were not included with the sample code. i.e. you cannot use stdio.h and stdlib.h)**

---

```c
// Your code here
```

## Question 3

**In C, write a function called `void renameFile(file_t *file, directory_t *parent, char *newFilename, char *newExtension)` that will rename file in the parent directory entry with the `newFilename` and `newExtension`.**

**You must modify the parent directory entry for this file properly to change the file name and extension. You can assume the file does have a directory entry in the directory. Once the parent directory is modified, write the changes back to the floppy disk using floppy_write().**

**(Assume you have all functions provided to you in the sample code provided for your OS.)**

**(You are not required to test the function in your OS project.)**

---

```c
// Your code here...
```

## Question 4

**In C, write a function called `int verifyFAT()` that will verify both copies of the FAT tables are consistent. If they are not consistent, overwrite the inconsistent FAT table entries with `0x0001`. If the FAT table had any entries overwritten with `0x0001`, write both copies of the FAT to the floppy disk.**

**Example: `if fat0->entries[5] == 6` and `fat1->entries[5] == 0`, then overwrite both so `fat0->entries[5] = 1` and `fat1->entries[5] = 1`.**

**If there are no inconsistencies, return 0, if there are inconsistencies, return a count of how many entries were inconsistent and were overwritten.**

**(Assume you have all functions provided to you in the sample code provided for your OS.)**

**(You are not required to test the function in your OS project.)**

---

```c
// Your code here...
```

## Question 5

**In C, write a function called `uint16 clusterCount(file_t *file)` that will count and return the number of clusters that the `file_t *file` occupies.**

**For example, if a `file_t *myFile` takes up 5 clusters, then `clusterCount(myFile)` should return `5`.**

**If there are inconsistent entries in the copies of the FAT tables for this file only, `return 0xFFFF`.**

**(Assume you are using all the sample code provided to you for the projects. You must use only the data types and functions that are accessible in your projects.)**

**(You are not required to test the function in your OS project.)**

---

```c
// Your code here...
```

## Question 6

**In C, write a function called `int moveCluster(uint16 clusterA, uint16 clusterB)` that will grab the data inside of the sector at file cluster `clusterA` and put it inside of sector for file cluster `clusterB`.**

**You must also update the FATs to reflect that this cluster has moved to a new cluster.**

**You must check if the file cluster `clusterB` is currently occupied via the FAT. If it is, `return -1`.**

**For example, if you call the function `moveCluster(3, 6)` this should be the FATs (before and after)**

### Before:


| Index | Entry |
| ----- | ----- |
| x0002 | x0003 |
| x0003 | x0004 |
| x0004 | xFFFF |
| x0005 |       |
| x0006 |       |

### After:

| Index | Entry |
| ----- | ----- |
| x0002 | x0006 |
| x0003 |       |
| x0004 | xFFFF |
| x0005 |       |
| x0006 | x0004 |

**Note: You still have to read the sector that is to be moved and write it to the new sector using `floppy_read()` and `floppy_write()`. If you only modify the FATs, your solution is not complete.**

**(Assume you are using all the sample code provided to you for the projects. You must use only the data types and functions that are accessible in your projects.)**

**(You are not required to test the function in your OS project.)**

---

```c
// Your code here...
```

## Question 7

**In C, write a function called void `renameFile(char *newFilename, char *newExt)` that will rename the currently opened file `(file_t currentFile)` in the currently opened directory `(directory_t currentDirectory)`.**

**You must modify `currentFile`'s directory entry `(directory_entry_t *directoryEntry)` for this file properly to change the file name and extension. Once the directory entry is modified, write the changes back to the floppy disk using `floppy_write()`. Assume the directory that the file is in is always the root directory.**

**(Assume you have all functions provided to you in the sample code provided for your OS.)**

**(You may not use any functions that you did not write or that were not included with the sample code. i.e. you cannot use stdio.h and stdlib.h)**

---

```c
// Your code here...
```

## Question 8

**In C, write a function called void `moveFile(directory_t *toDirectory)` that will move the currently opened file `(file_t currentFile)` in the currently opened directory `(directory_t currentDirectory)` to the new directory `(directory_t *toDirectory)`.**

**You must modify `currentDirectory`'s directory entry `(directory_entry_t *directoryEntry)` and `toDirectory`'s directory entry to properly move the file. Essentially, copy the 32 bytes of the directory entry for the current file from the current directory to the new directory. Once the directory entry is modified, write the changes back to the floppy disk using `floppy_write()`. Assume the current directory that the file is originally in is always the root directory, and assume the directory the file is moved to takes up only 1 cluster and can be found at `toDirectory->directoryEntry->startingCluster`.**

**(Assume you have all functions provided to you in the sample code provided for your OS.)**

**(You may not use any functions that you did not write or that were not included with the sample code. i.e. you cannot use stdio.h and stdlib.h)**

**(This function cannot really be tested with our sample code. Try to get your function as close as possible to a valid solution, you do not have to test it but it should compile.)**

---

```c
// Your code here...
```

