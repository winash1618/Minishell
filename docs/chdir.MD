# chdir - change working directory
## Resources
- https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/#:~:text=The%20chdir%20command%20is%20a,the%20directory%20specified%20in%20path
- https://man7.org/linux/man-pages/man2/chdir.2.html
## Synopsis
```
       #include <unistd.h>
       int chdir(const char *path);
```
## Description
- chdir() changes the current working directory of the calling
       process to the directory specified in path.
## Return value
- On success, zero is returned.
- On error, -1 is returned.
## Sample program
```
#include<stdio.h>
  
// chdir function is declared
// inside this header
#include<unistd.h> 
int main()
{   
    char s[100];
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // using the command
    chdir("..");
  
    // printing current working directory
    printf("%s\n", getcwd(s, 100));
  
    // after chdir is executed
    return 0;
}
```
- Out put 
```
mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out
/Users/mkaruvan/Desktop/minishell/minishell learning process/intro_to_allowed_functions
/Users/mkaruvan/Desktop/minishell/minishell learning process
mkaruvan@lab3r3s10 intro_to_allowed_functions %
```
- Note:The above program changes the working directory of a process. But, it doesn’t change the working directory of current shell. Because when the program is executed in the shell, the shell follows fork on exec mechanism. So, it doesn’t affect the current shell.
```
#include <unistd.h>
#include <stdio.h>
  
// Main Method
int main() {
  
  // changing the current 
  // working directory(cwd)
  // to /usr
  if (chdir("/usr") != 0) 
    perror("chdir() to /usr failed");
  
  // changing the cwd to /tmp
  if (chdir("/tmp") != 0) 
    perror("chdir() to /temp failed");
  
  // there is no /error 
  // directory in my pc
  if (chdir("/error") != 0) 
  
    // so chdir will return -1 
    perror("chdir() to /error failed");  
  
  return 0;
}
```
- Out put:
```
mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out    
chdir() to /error failed: No such file or directory
mkaruvan@lab3r3s10 intro_to_allowed_functions %
```
- Note: if you want to give relative path "chdir("..");" donot put slash. if you want absolute path "chdir("/tmp")" put slash.
