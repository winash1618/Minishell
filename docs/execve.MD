# execve - execute program
## Resources
- https://people.cs.rutgers.edu/~pxk/416/notes/c-tutorials/exec.html
- https://man7.org/linux/man-pages/man2/execve.2.html
- https://stackoverflow.com/questions/10321435/is-char-envp-as-a-third-argument-to-main-portable ---envp---
- https://stackoverflow.com/questions/10649273/where-is-the-definition-of-extern-char-environ ---environ---
## Synopsis
```
       #include <unistd.h>
       
       int execve(const char *pathname, char *const argv[],
                  char *const envp[]);
```
## Description
- execve() executes the program referred to by pathname.  This
causes the program that is currently being run by the calling
process to be replaced with a new program, with newly initialized
stack, heap, and (initialized and uninitialized) data segments.
pathname must be either a binary executable or Interpreter scripts.
- argv is an array of pointers to strings passed to the new program
as its command-line arguments.  By convention, the first of these
strings (i.e., argv[0]) should contain the filename associated
with the file being executed.  The argv array must be terminated
by a NULL pointer.  (Thus, in the new program, argv[argc] will be
NULL.)
- envp is an array of pointers to strings, conventionally of the
form key=value, which are passed as the environment of the new
program.  The envp array must be terminated by a NULL pointer.

- The argument vector and environment can be accessed by the new
program's main function, when it is defined as:
```
  int main(int argc, char *argv[], char *envp[])
```
- Note, however, that the use of a third argument to the main
function is not specified in POSIX.1; according to POSIX.1, the
environment should be accessed via the external variable
environ(7).
- Note : One sometimes sees execve() (and the related functions described
in exec(3)) described as "executing a new process" (or similar).
This is a highly misleading description: there is no new process;
many attributes of the calling process remain unchanged (in
particular, its PID).  All that execve() does is arrange for an
existing process (the calling process) to execute a new program.
##
-Effects of execve()
A file descriptor opens when an execve system call is made and remains open in the new process until it is closed by fcntl. This is the aspect used to specify the standard streams like stdin, stdout, and stderr for the new program. When the overlay of the new process is successfully done, then the memory address space for the previous method and all memory area that was not shared was isolated and again returned to the operating system. At the same time, the data that is not shared with the new program is lost.
## Return value
- On success, execve() does not return, 
- on error -1 is returned.
## Sample program
- The following program is designed to be execed by the second
 program below.  It just echoes its command-line arguments, one
 per line.
 ```
           /* myecho.c */

           #include <stdio.h>
           #include <stdlib.h>

           int
           main(int argc, char *argv[])
           {
               for (int j = 0; j < argc; j++)
                   printf("argv[%d]: %s\n", j, argv[j]);

               exit(EXIT_SUCCESS);
           }

 ```
 - This program can be used to exec the program named in its
 command-line argument:
```
           /* execve.c */

           #include <stdio.h>
           #include <stdlib.h>
           #include <unistd.h>

           int
           main(int argc, char *argv[])
           {
               char *newargv[] = { NULL, "hello", "world", NULL };
               char *newenviron[] = { NULL };

               if (argc != 2) {
                   fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
                   exit(EXIT_FAILURE);
               }

               newargv[0] = argv[1];

               execve(argv[1], newargv, newenviron);
               perror("execve");   /* execve() returns only on error */
               exit(EXIT_FAILURE);
           }
```
-We can use the second program to exec the first as follows:
```
           $ cc myecho.c -o myecho
           $ cc execve.c -o execve
           $ ./execve ./myecho
```
- Out put
```
          argv[0]: ./myecho
           argv[1]: hello
           argv[2]: world
```
- Example 2: Here we will execute a predefined process /bin/ls
```
  #include <stdlib.h>	/* needed to define exit() */
  #include <unistd.h>	/* needed to define getpid() */
  #include <stdio.h>	/* needed for printf() */

  int
  main(int argc, char **argv) {
    char *args[] = {"ls", "-aF", "/", 0};	/* each element represents a command line argument */
    char *env[] = { 0 };	/* leave the environment list null */

    printf("About to run /bin/ls\n");
    execve("/bin/ls", args, env);
    perror("execve");	/* if we get here, execve failed */
    exit(1);
  }
```
-Out put
- It will return ls result of the root directory since the path name provided is '/' which is root directory.
```
mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out
About to run /bin/ls
./                      .vol/                   dev/                    sbin/
../                     Applications/           etc@                    sgoinfre@
.DS_Store               Library/                exam/                   tmp@
.Spotlight-V100/        System/                 goinfre/                usr/
.Trashes/               Users/                  iSCSI/                  var@
.VolumeIcon.icns@       Volumes/                nfs/
.file                   bin/                    opt/
.fseventsd/             cores/                  private/
mkaruvan@lab3r3s10 intro_to_allowed_functions %
```

