# wait, waitpid - wait for process to change state
## Resources
- https://stackoverflow.com/questions/24130990/i-used-waitstatus-and-the-value-of-status-is-256-why
- https://stackoverflow.com/questions/23709888/how-to-use-wait-in-c
- https://man7.org/linux/man-pages/man2/wait.2.html
- https://www.geeksforgeeks.org/wait-system-call-c/
## Synopsis
```
       #include <sys/wait.h>
       pid_t wait(int *wstatus);
       pid_t waitpid(pid_t pid, int *wstatus, int options);
```
## Description
- All of these system calls are used to wait for state changes in a child of the calling process, and obtain information about the child whose state has changed.  A state change is considered to be: the child terminated; the child was stopped by a signal; or the child was resumed by a signal.  In the case of a terminated child, performing a wait allows the system to release the resources associated with the child; if a wait is not performed, then the terminated child remains in a "zombie" state.
- If a child has already changed state, then these calls return
immediately.  Otherwise, they block until either a child changes
state or a signal handler interrupts the call
- In the remainder of this page, a child
whose state has changed and which has not yet been waited upon by
one of these system calls is termed waitable.
- The wait() system call suspends execution of the calling thread
until one of its children terminates.  The call wait(&wstatus) is
equivalent to:
```
waitpid(-1, &wstatus, 0);
```
- The waitpid() system call suspends execution of the calling
 thread until a child specified by pid argument has changed state.
 By default, waitpid() waits only for terminated children, but
 this behavior is modifiable via the options argument, as
 described below.
 ```
        The value of pid can be:

       < -1   meaning wait for any child process whose process group ID
              is equal to the absolute value of pid.

       -1     meaning wait for any child process.

       0      meaning wait for any child process whose process group ID
              is equal to that of the calling process at the time of the
              call to waitpid().

       > 0    meaning wait for the child whose process ID is equal to
              the value of pid.
```
```
       The value of options is an OR of zero or more of the following
       constants:

       WNOHANG
              return immediately if no child has exited.

       WUNTRACED
              also return if a child has stopped.  Status for traced children which have stopped
              is provided even if this option is not specified.

       WCONTINUED
              also return if a stopped child has been resumed by
              delivery of SIGCONT.
 ```
 ## Return values
 - wait(): on success, returns the process ID of the terminated
 child; on failure, -1 is returned.
 - waitpid(): on success, returns the process ID of the child whose
 state has changed; if WNOHANG was specified and one or more
 child(ren) specified by pid exist, but have not yet changed
 state, then 0 is returned.  On failure, -1 is returned.   
 ## What is the difference between a wait () and sleep ()?
 - Both sleep() and wait() are used to put the current thread on hold, but they were designed for different use cases: There must be someone outside who will wake up the thread by calling notify() or notifyAll() on the monitor (on the same object that was used to call wait() ).
 - wait() is used for inter-thread communication while sleep() is used to introduce pause on execution, generally. Thread. sleep() sends the current thread into the “Not Runnable” state for some amount of time.
## Child status information: 
- Status information about the child reported by wait is more than just the exit status of the child, it also includes 
       - normal/abnormal termination
       - termination cause
       - exit status
- For find information about status, we use 
```
WIF….macros
       1. WIFEXITED(status): child exited normally 
       • WEXITSTATUS(status): return code when child exits
       2. WIFSIGNALED(status): child exited because a signal was not caught 
       • WTERMSIG(status): gives the number of the terminating signal
       3. WIFSTOPPED(status): child is stopped 
       • WSTOPSIG(status): gives the number of the stop signal
```
## Sample programs:
- C program to demonstrate working of wait()
```
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
 
int main()
{
    pid_t cpid;
    if (fork()== 0)
        exit(0);           /* terminate child */
    else
        cpid = wait(NULL); /* reaping parent */
    printf("Parent pid = %d\n", getpid());
    printf("Child pid = %d\n", cpid);
 
    return 0;
}
```
- Out put
```
Parent pid = 90170
Child pid = 90171
```
- C program to demonstrate working of status from wait.
```
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
 
void waitexample()
{
    int stat;
 
    // This status 1 is reported by WEXITSTATUS
    if (fork() == 0)
        exit(1);
    else
        wait(&stat);
    if (WIFEXITED(stat))
        printf("Exit status: %d\n", WEXITSTATUS(stat));
    else if (WIFSIGNALED(stat))
        psignal(WTERMSIG(stat), "Exit signal");
}
 
// Driver code
int main()
{
    waitexample();
    return 0;
}
```
- Out put
```
       Exit status: 1 
```
- C program to demonstrate waitpid()
```
       #include<stdio.h>
       #include<stdlib.h>
       #include<sys/wait.h>
       #include<unistd.h>

       void waitexample()
       {
           int i, stat;
           pid_t pid[5];
           for (i=0; i<5; i++)
           {
               if ((pid[i] = fork()) == 0)
               {
                   sleep(1);
                   exit(100 + i);
               }
           }

           // Using waitpid() and printing exit status
           // of children.
           for (i=0; i<5; i++)
           {
               pid_t cpid = waitpid(pid[i], &stat, 0);
               if (WIFEXITED(stat))
                   printf("Child %d terminated with status: %d\n",
                          cpid, WEXITSTATUS(stat));
           }
       }

       // Driver code
       int main()
       {
           waitexample();
           return 0;
       }
```
- Out put
```
       Child 91216 terminated with status: 100
       Child 91217 terminated with status: 101
       Child 91218 terminated with status: 102
       Child 91219 terminated with status: 103
       Child 91220 terminated with status: 104
```
##  wait3, wait4 - wait for process to change state, BSD style
### Synopsis
```
       #include <sys/wait.h>

       pid_t wait3(int *wstatus, int options, struct rusage *rusage);
       pid_t wait4(pid_t pid, int *wstatus, int options,
                   struct rusage *rusage);
```
### Description
- These functions are nonstandard; in new programs, the use of
       waitpid(2) or waitid(2) is preferable.
- The wait3() and wait4() system calls are similar to waitpid(2),
       but additionally return resource usage information about the
       child in the structure pointed to by rusage.
- Other than the use of the rusage argument, the following wait3()
       call:
```
       wait3(wstatus, options, rusage);
```
- is equivalent to:
```
       waitpid(-1, wstatus, options);
```
- Similarly, the following wait4() call:
```
       wait4(pid, wstatus, options, rusage);
```
- is equivalent to:
```
       waitpid(pid, wstatus, options);
```
- In other words, wait3() waits of any child, while wait4() can be
       used to select a specific child, or children, on which to wait.
       See wait(2) for further details.
- If rusage is not NULL, the struct rusage to which it points will
       be filled with accounting information about the child. A structure representing an accounting of resource utilization.  
### Return values
- Return values are same as waitpid.


       
       
