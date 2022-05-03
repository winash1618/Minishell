// #include<stdio.h>
  
// // chdir function is declared
// // inside this header
// #include<unistd.h> 
// int main()
// {   
//     char s[100];
  
//     // printing current working directory
//     printf("%s\n", getcwd(s, 100));
  
//     // using the command
//     chdir("..");
  
//     // printing current working directory
//     printf("%s\n", getcwd(s, 100));
  
//     // after chdir is executed
//     return 0;
// }

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
