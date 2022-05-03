# pipe - create pipe
## Resources
- https://man7.org/linux/man-pages/man2/pipe.2.html
- https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
- https://www.geeksforgeeks.org/pipe-system-call/
## Synopsis
```
       #include <unistd.h>

       int pipe(int pipefd[2]);
```
## Description
- pipe() creates a pipe, a unidirectional data channel that can be
used for interprocess communication.  
- The array pipefd is used to
return two file descriptors referring to the ends of the pipe.
- pipefd[0] refers to the read end of the pipe.  
- pipefd[1] refers to the write end of the pipe.  
- Data written to the write end of
the pipe is buffered by the kernel until it is read from the read
end of the pipe.
- In UNIX Operating System, Pipes are useful for communication between related processes(inter-process communication).
- Pipe is one-way communication only i.e we can use a pipe such that One process write to the pipe, and the other process reads from the pipe. It opens a pipe, which is an area of main memory that is treated as a “virtual file”.
- Pipe can be used for communication between parent and the child created by fork. One process can write to the “virtual file” or pipe and another related process can read from it.
## Return value
- On success, zero is returned.  
- On error, -1 is returned.

![Process](https://user-images.githubusercontent.com/51042907/166400211-05d9c350-d994-4e49-9ccf-eb1e33ccbdf4.jpg)

## Sample program
- Let's see a C program to illustrate pipe function.
```
#include <stdio.h>
#include <unistd.h>
#define MSGSIZE 16
char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";

int main()
{
	char inbuf[MSGSIZE];
	int p[2], i;

	if (pipe(p) < 0)
		exit(1);

	/* continued */
	/* write pipe */

	write(p[1], msg1, MSGSIZE);
	write(p[1], msg2, MSGSIZE);
	write(p[1], msg3, MSGSIZE);

	for (i = 0; i < 3; i++) {
		/* read pipe */
		read(p[0], inbuf, MSGSIZE);
		printf("% s\n", inbuf);
	}
	return 0;
}
```
- Out put:
```
hello, world #1
hello, world #2
hello, world #3
```
- Let's see a C pogram that illustrates parent and child sharing a pipe
```
// C program to illustrate
// pipe system call in C
// shared by Parent and Child
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MSGSIZE 16
char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";

int main()
{
	char inbuf[MSGSIZE];
	int p[2], pid, nbytes;

	if (pipe(p) < 0)
		exit(1);

	/* continued */
	if ((pid = fork()) > 0) {
		write(p[1], msg1, MSGSIZE);
		write(p[1], msg2, MSGSIZE);
		write(p[1], msg3, MSGSIZE);

		// Adding this line will
		// not hang the program
		// close(p[1]);
		wait(NULL);
	}

	else {
		// Adding this line will
		// not hang the program
		// close(p[1]);
		while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0)
			printf("% s\n", inbuf);
		if (nbytes != 0)
			exit(2);
		printf("Finished reading\n");
	}
	return 0;
}
```
- Out put
```
hello world, #1
hello world, #2
hello world, #3
(hangs)         //program does not terminate but hangs
```
- Here, In this code After finishing reading/writing, both parent and child block instead of terminating the process and that’s why program hangs. This happens because read system call gets as much data it requests or as much data as the pipe has, whichever is less.
  - If pipe is empty and we call read system call then Reads on the pipe will return EOF (return value 0) if no process has the write end open.
  - If some other process has the pipe open for writing, read will block in anticipation of new data so this code output hangs because here write ends parent process and also child process doesn’t close.
