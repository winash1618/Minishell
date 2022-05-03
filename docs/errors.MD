# strerror - return string describing error number
## Resources
- https://www.tutorialspoint.com/c_standard_library/c_function_strerror.htm
- https://man7.org/linux/man-pages/man3/strerror.3.html
## Synopsis
```
       #include <string.h>

       char *strerror(int errnum);
```
## Description
- The strerror() function returns a pointer to a string that
describes the error code passed in the argument errnum.
## Return value
- The strerror() functions return the appropriate error description string.
- or an "Unknown error nnn" message if the error number is unknown.
## Sample program
- Let's see a C program that illustrates the working of strerror function.
``` 
  #include <stdio.h>
  #include <string.h>
  #include <errno.h>

  int main () {
     FILE *fp;

     fp = fopen("file.txt","r");
     if( fp == NULL ) {
        printf("Error: %s\n", strerror(errno));
     }

     return(0);
  }
```
- Out put
```
  mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out
  Error: No such file or directory
  mkaruvan@lab3r3s10 intro_to_allowed_functions % 
```
# perror - print a system error message
## Synopsis
```
       #include <stdio.h>

       void perror(const char *s);
```
## Description
- The perror() function produces a message on standard error
describing the last error encountered during a call to a system
or library function.
- First (if s is not NULL and *s is not a null byte ('\0')), the
argument string s is printed, followed by a colon and a blank.
Then an error message corresponding to the current value of errno
and a new-line.
## Sample program
```
  #include <stdio.h>

  int main () {
     FILE *fp;

     /* first rename if there is any file */
     rename("file.txt", "newfile.txt");

     /* now let's try to open same file */
     fp = fopen("file.txt", "r");
     if( fp == NULL ) {
        perror("Error");
        return(-1);
     }
     fclose(fp);

     return(0);
  }
```
- Out put
```
  mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out     
  Error: No such file or directory
  mkaruvan@lab3r3s10 intro_to_allowed_functions % 
```
