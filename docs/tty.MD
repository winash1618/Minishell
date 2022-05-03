# ttyname - return name of a terminal
## Resources
- https://c-for-dummies.com/blog/?p=4385
- https://man7.org/linux/man-pages/man3/ttyslot.3.html
- https://man7.org/linux/man-pages/man3/ttyname.3.html
## Synopsis
```
       #include <unistd.h>

       char *ttyname(int fd);
```
## Description
- In Linux and Unix, the terminal is assigned a name. Specifically, it’s the name of a file located in the /dev directory. This configuration is necessary because the operating system treats all devices as files. Like a file, you can read and write from the terminal; it’s an I/O device. To get started, you must know the current terminal’s filename.
- The ttyname() function obtains the name of a terminal.
- The function ttyname() returns a pointer to the null-terminated
pathname of the terminal device that is open on the file
descriptor fd, or NULL on error (for example, if fd is not
connected to a terminal).  
- The return value may point to static data, possibly overwritten by the next call. 
## Return value
- The function ttyname() returns a pointer to a pathname on
       success.  
- On error, NULL is returned,
## Sample program
- Let's look at a simple C program that illustrate the working ttyname function. The ttyname() function is called with argument 0. This value represents the file descriptor for the standard input device, stdin, which is the current terminal.
```
  #include <stdio.h>
  #include <unistd.h>

  int main()
  {
      char *term;

      term = ttyname(0);
      printf("This is terminal %s\n",term);

      return(0);
  }
```
- Out put
```
mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out
This is terminal /dev/ttys001
mkaruvan@lab3r3s10 intro_to_allowed_functions % 
```
- Once you know the terminal’s filename, you can open it for I/O just like any other file. You can use the formatted file functions, as demonstrated in this code:
```
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>

  int main()
  {
      char *term;
      FILE *tout;

      /* obtain terminal name and open */
      term = ttyname(0);
      tout = fopen(term,"w");
      if( tout==NULL )
      {
          fprintf(stderr,"Unable to open %s\n",term);
          exit(1);
      }

      /* send text to the terminal */
      fprintf(tout,"Hello, terminal %s\n",term);

      /* close */
      fclose(tout);

      return(0);
  }
```
- The terminal filename is obtained at Line 11: term = ttyname(0); The next statement attempts to open this file for writing (output) by using the fopen() function: tout = fopen(term,"w"); The tout file handle is then tested to ensure that the file was opened.
- Out put
```
mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out      
Hello, terminal /dev/ttys001
mkaruvan@lab3r3s10 intro_to_allowed_functions
```
-Of course, you could always just write to standard output; the output goes to the current terminal by default. Yet in this sample code, the terminal’s device/filename was obtained, opened for output, then the output is sent via the terminal’s file/device instead. It’s a roundabout way of doing things, but it drives home the point that all devices in Unix are files and can be treated as such.
# ttyslot - find the slot of the current user's terminal in some file
## Synopsis
```
       #include <unistd.h>       /* See NOTES */

       int ttyslot(void);
```
## Description
- The legacy function ttyslot() returns the index of the current user's entry in some file.
- Not much details are there about this function.
## Return value
- If successful, this function returns the slot number.
- On error you need to check that because it is either 0 or -1 depending on the system you are using.


