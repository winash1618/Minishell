# getcwd - get current working directory
## Resources
- https://man7.org/linux/man-pages/man3/getcwd.3.html
- https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
## Synopsis
```
#include <unistd.h>
char *getcwd(char *buf, size_t size);
```
## Description
- These functions return a null-terminated string containing an
 absolute pathname that is the current working directory of the
 calling process.  The pathname is returned as the function result
 and via the argument buf, if present, which is of length size.
- If the length of the absolute pathname of the current working
directory, including the terminating null byte, exceeds size
bytes, NULL is returned,
- glibc's getcwd() allocates the buffer dynamically using malloc(3) if buf is NULL.
In this case, the allocated buffer has the length size unless
size is zero, when buf is allocated as big as necessary.  The
caller should free(3) the returned buffer.
## Return value
- On success, these functions return a pointer to a string containing the pathname of the current working directory.
- On failure, these functions return NULL
## Sample program
```
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int main() {
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}
```
- Out put
```
  Current working dir: /Users/mkaruvan/Desktop/minishell/minishell learning process/intro_to_allowed_functions
```
