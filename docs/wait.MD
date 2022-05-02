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


 
