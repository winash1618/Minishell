# fork - create a child process
## Resources
- https://www.interviewkickstart.com/learn/fork-in-c
- https://man7.org/linux/man-pages/man2/fork.2.html
- https://www.geeksforgeeks.org/fork-system-call/
## Synopsis
```
       #include <unistd.h>
       pid_t fork(void);
```
## Description
   - fork() creates a new process by duplicating the calling process.
   The new process is referred to as the child process.  The calling
   process is referred to as the parent process.
   - The child process and the parent process run in separate memory
   spaces.  At the time of fork() both memory spaces have the same
   content. 
   - Only the shared memory segments are shared between the
   parent process and the newly forked child process. Copies of the stack
   and the heap are made for the newly created process.
   - The child process is an exact duplicate of the parent process
   except for the following points:
     - The child has its own unique process ID.
     - separate program counter (PC) indicating where to execute next
## Return values
  - On success, the PID of the child process is returned in the parent.
  - and 0 is returned in the child.
  - On failure, -1 is returned in the parent, no child process is created.


       
