# dup, dup2 - duplicate a file descriptor
## Resources

## Synopsis
```
       #include <unistd.h>

       int dup(int oldfd);
       int dup2(int oldfd, int newfd);
```
## Description
### dup()
- The dup() system call allocates a new file descriptor that refers
to the same open file description as the descriptor oldfd.   The new
file descriptor number is guaranteed to be the lowest-numbered
file descriptor that was unused in the calling process.
- After a successful return, the old and new file descriptors may
be used interchangeably.  Since the two file descriptors refer to
the same open file description, they share file offset and file
status flags; for example, if the file offset is modified by
using lseek(2) on one of the file descriptors, the offset is also
changed for the other file descriptor.
### dup2()
- The dup2() system call performs the same task as dup(), but
instead of using the lowest-numbered unused file descriptor, it
uses the file descriptor number specified in newfd.
-  If the file descriptor newfd was previously open, it is closed
before being reused; the close is performed silently (i.e., any
errors during the close are not reported by dup2()).
- If oldfd is not a valid file descriptor, then the call fails,
and newfd is not closed.
- If oldfd is a valid file descriptor, and newfd has the same
value as oldfd, then dup2() does nothing, and returns newfd.
- A tricky use of dup2() system call : As in dup2(), in place of newfd any file descriptor can be put. Below is a C implementation in which the file descriptor of Standard output (stdout) is used. This will lead all the printf() statements to be written in the file referred by the old file descriptor.
## Return value
- On success, these system calls return the new file descriptor.
- On error, -1 is returned
## Sample program
- Let's see a C program to illustrate dup()
```
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	// open() returns a file descriptor file_desc to a
	// the file "dup.txt" here"

	int file_desc = open("dup.txt", O_WRONLY | O_APPEND);
	
	if(file_desc < 0)
		printf("Error opening the file\n");
	
	// dup() will create the copy of file_desc as the copy_desc
	// then both can be used interchangeably.

	int copy_desc = dup(file_desc);
		
	// write() will write the given string into the file
	// referred by the file descriptors

	write(copy_desc,"This will be output to the file named dup.txt\n", 46);
		
	write(file_desc,"This will also be output to the file named dup.txt\n", 51);
	
	return 0;
}
```
- Out put: There will be no output on stdout since we not printing anything but you can look at the file dup.txt inorder to the see the changes.
- Let's look at a C program to illustrate dup2()
```
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main()
{
    int file_desc = open("tricky.txt",O_RDWR | O_APPEND | O_CREAT);
      
    // here the newfd is the file descriptor of stdout (i.e. 1)
    dup2(file_desc, 1) ; 
          
    // All the printf statements will be written in the file
    // "tricky.txt"
    printf("I will be printed in the file tricky.txt\n");
      
return 0;
}
```
- Out put: Eventhough we are printing something in above program we won't see any changes in the stdout instead we will see the printf result in tricky.txt since dup2() changed the default file descriptor for stdout to file descriptor of the tricky.txt so that whatever given to printf to print will be written inside tricky.txt.
