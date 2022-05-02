# fork - create a child process
## Resources
- https://www.interviewkickstart.com/learn/fork-in-c
- https://man7.org/linux/man-pages/man2/fork.2.html
- https://www.geeksforgeeks.org/fork-system-call/
- https://stackoverflow.com/questions/4298678/after-forking-are-global-variablesshared#:~:text=The%20child%20is%20an%20exact,a%20call%20to%20fork()
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
   - After fork(), the entire process, including all global variables, is duplicated. The child is an exact replica of the parent, except that it has a different PID(Process Id), a different parent, and fork() returned 0. Global variables are still global within its own process. So the answer is no, global variables are not shared between processes after a call to fork().
   - The child process is an exact duplicate of the parent process
   except for the following points:
     - The child has its own unique process ID.
     - separate program counter (PC) indicating where to execute next
## Return values
  - On success, the PID of the child process is returned in the parent.
  - and 0 is returned in the child.
  - On failure, -1 is returned in the parent, no child process is created.
## Difference between exec and fork functions.

  ![613703a693062c71baec8698_whats-the-difference-between-fork-and-exec-function-in-c](https://user-images.githubusercontent.com/51042907/166195835-c18b45d9-abae-45d1-9894-0def13bf44a9.jpg)


## Sample program
  - Example 1:
  ```
       #include <stdio.h>
       #include <unistd.h>

       int main()
       {
              fork();
              printf("If the fork function is successful in creating a child process, I will print twice.\n");
              return 0;
       }
  ```
  - Out put:
  ```
       If the fork function is successful in creating a child process, I will print twice.
       If the fork function is successful in creating a child process, I will print twice.
  ```
  - Example 2:
  ```
       #include <stdio.h>
       #include <unistd.h>

       int main()
       {
              int processID= fork();
              if(processID>0)
                     printf("fork() returned a +ve value. This is the parent process, with ID: %d \n",getpid());
              else if(processID==0)
              {
                     printf("fork() returned a 0 value. This is a newly created child process with ID: %d \n",getpid());
                     printf("The parent process of this child process has the ID: %d\n",getppid());
              }
              else
                     printf("fork() returned a -ve value, so the fork system called failed and the child process could not be created\n");
              printf("This is a single print statement. If the fork() system call was successful, both the parent and child process will run concurrently, and this statement will print twice.\n");
              return 0;
       }
  ```
  - Out put:
  ```
       fork() returned a +ve value. This is the parent process, with ID: 77225 
       This is a single print statement. If the fork() system call was successful, both the parent and child process will run concurrently, and this statement will print twice.
       fork() returned a 0 value. This is a newly created child process with ID: 77226 
       The parent process of this child process has the ID: 1
       This is a single print statement. If the fork() system call was successful, both the parent and child process will run concurrently, and this statement will print twice.
  ```

- Example 3
```
       #include <stdio.h>
       #include <unistd.h>
       int main()
       {
              fork();
              fork();
              fork();
              printf("The fork function was called three times. I should print eight times.\n");
              return 0;
       }
```
- Out put:
```
       The fork function was called three times. I should print eight times.
       The fork function was called three times. I should print eight times.
       The fork function was called three times. I should print eight times.
       The fork function was called three times. I should print eight times.
       The fork function was called three times. I should print eight times.                                      
       The fork function was called three times. I should print eight times.
       The fork function was called three times. I should print eight times.
       The fork function was called three times. I should print eight times.
```


       
