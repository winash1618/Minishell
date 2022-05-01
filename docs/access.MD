# Access - check user's permissions for a file
## Synopsis
```
  #include <unistd.h>
  int access(const char *pathname, int mode);
```
## Description
- In Linux, access command is used to check whether the calling program has access to a specified file. It can be used to check whether a file exists or not. The check is done using the calling process’s real UID and GID.
- Here, the first argument takes the path to the directory/file and the second argument takes flags R_OK, W_OK, X_OK or F_OK.
```
  F_OK flag : Used to check for existence of file.
  R_OK flag : Used to check for read permission bit.
  W_OK flag : Used to check for write permission bit.
  X_OK flag : Used to check for execute permission bit.
```
## Return value:
- If access() cannot access the file, it will return -1 or else it will be 0.
## Sample programs
- Example 1 : F_OK flag
```
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
  
extern int errno;
  
int main(int argc, const char *argv[]){
    int fd = access("sample.txt", F_OK);
    if(fd == -1){
            printf("Error Number : %d\n", errno);
        perror("Error Description:");
    }
        else
                printf("No error\n");
    return 0;
}
```
- Explanation: In the output, we get the message “No error” because the file is present in the current directory. If the file does not exist, the value of fd will become -1. In the above code, the only possible way we will get an error is if the file doesn’t exist for the specified path. It can also give an error if the pathname is too long.
- Example 2 : Check for all permission bits (read, write, execute)
```
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
  
extern int errno;
  
int main(int argc, const char *argv[]){
    int fd = access("sample.txt", (R_OK | W_OK) & X_OK);
    if(fd == -1){
        printf("Error Number : %d\n", errno);
        perror("Error Description:");
    }
    else{
        printf("No error\n");
    }
    return 0;
}
```
- Explanation: In the output, the write and execute user permission bits were set and since we were testing for a case where (R_OK | W_OK) & X_OK, we get no error. The file descriptor value is 0. We can use bitwise operations to decide the mode argument in access() system call.


