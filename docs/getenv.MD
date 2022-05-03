# getenv - get an environment variable
## Resources
- https://www.tutorialspoint.com/c_standard_library/c_function_getenv.htm
- https://linuxhint.com/getenv-function-usage/
- https://man7.org/linux/man-pages/man3/getenv.3.html
## Synopsis
```
       #include <stdlib.h>

       char *getenv(const char *name);
```
## Description
- The getenv() function searches the environment list to find the
environment variable name, and returns a pointer to the
corresponding value string.
- The getenv() works In such a way that it searches the environment variable dynamically at the run time in every entry along with the specific name. When it is found, it returns a pointer to the value of a variable. The C source code or program must be written in such a way that it does not modify the string that is addressed by the pointer and returned by getenv().
## Return value 
- The getenv() function returns a pointer to the value in the
environment, 
- or NULL if there is no match.
## Sample program
- The following example shows the usage of getenv() function.
```
  #include <stdio.h>
  #include <stdlib.h>

  int main () {
     printf("PATH : %s\n", getenv("PATH"));
     printf("HOME : %s\n", getenv("HOME"));
     printf("ROOT : %s\n", getenv("ROOT"));

     return(0);
  }
```
- Out put
```
  mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out
  PATH : /usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/mkaruvan/Desktop/42-ValgrindContainer:/Users/mkaruvan/Desktop/42-ValgrindContainer
  HOME : /Users/mkaruvan
  ROOT : (null)
  mkaruvan@lab3r3s10 intro_to_allowed_functions %
```

