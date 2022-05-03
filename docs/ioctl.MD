# ioctl - control device
## Resources
- https://man7.org/linux/man-pages/man2/ioctl.2.html
- https://linuxhint.com/c-ioctl-function-usage/
- https://www.opensourceforu.com/2011/08/io-control-in-linux/
- https://stackoverflow.com/questions/15807846/ioctl-linux-device-driver
- https://stackoverflow.com/questions/2264384/how-do-i-use-ioctl-to-manipulate-my-kernel-module
## Synopsis
```
       #include <sys/ioctl.h>

       int ioctl(int fd, unsigned long request, ...);
```
## Description
- The ioctl function is useful for implementing a device driver to set the configuration on the device. e.g. a printer that has configuration options to check and set the font family, font size etc. ioctl could be used to get the current font as well as set the font to a new one. A user application uses ioctl to send a code to a printer telling it to return the current font or to set the font to a new one.
- The simple files of a Linux-based system can easily be read or written using simple input and output operations. However, there are some other complex types of files too that cannot be accessed with the help of simple input and output functions. We use the “IOCTL” function of the C programming language for all such files. It stands for “Input/ Output Control.”
- The Purpose of the IOCTL Function in C : Apart from the regular files of a system, there are some special purpose files, such as the device files. The device files are the ones that are used to interact with the different device drivers of a system. However, you cannot access these device files with the help of regular system calls. This is where the “IOCTL” function comes into play. This function helps in accessing these files very conveniently. The “IOCTL” function of the C programming language resides inside the “ioctl.h” header file.
- The ioctl need much more time to learn since they are dealing with kernel and stuff. for now i am going to get brief explanation on how this function work.
- The first arguement fd is a file descriptor and it must be open.
- The second argument is a device-dependent request code. This is where magic hapens i am going to try and explain this in a little bit more detail.
  - int request is not just a macro. A user application is required to generate a request code and the device driver module to determine which configuration on device must be played with. The application sends the request code using ioctl and then uses the request code in the device driver module to determine which action to perform.
  - A request code has 4 main parts
  ```
    1. A Magic number - 8 bits
    2. A sequence number - 8 bits
    3. Argument type (typically 14 bits), if any.
    4. Direction of data transfer (2 bits).  
  ```
  - If the request code is SETFONT to set font on a printer, the direction for data transfer will be from user application to device driver module (The user application sends the font name "Arial" to the printer). If the request code is GETFONT, direction is from printer to the user application.
  - In order to generate a request code, Linux provides some predefined function-like macros.
    - _IO(MAGIC, SEQ_NO) both are 8 bits, 0 to 255, e.g. let us say we want to pause printer. This does not require a data transfer. So we would generate the request code as below
    ```
        #define PRIN_MAGIC 'P'
            #define NUM 0
            #define PAUSE_PRIN __IO(PRIN_MAGIC, NUM) 
    ```
      - and now use ioctl as
    ```
     ret_val = ioctl(fd, PAUSE_PRIN);
    ```
      - The corresponding system call in the driver module will receive the code and pause the printer.
    - __IOW(MAGIC, SEQ_NO, TYPE) MAGIC and SEQ_NO are the same as above, and TYPE gives the type of the next argument, recall the third argument of ioctl is void *. W in __IOW indicates that the data flow is from user application to driver module. As an example, suppose we want to set the printer font to "Arial".
    ```
      #define PRIN_MAGIC 'S'
      #define SEQ_NO 1
      #define SETFONT __IOW(PRIN_MAGIC, SEQ_NO, unsigned long)
    ```
      - further,
    ```
      char *font = "Arial";
      ret_val = ioctl(fd, SETFONT, font); 
    ```
    - Now font is a pointer, which means it is an address best represented as unsigned long, hence the third part of _IOW mentions type as such. Also, this address of font is passed to corresponding system call implemented in device driver module as unsigned long and we need to cast it to proper type before using it. Kernel space can access user space and hence this works. other two function-like macros are __IOR(MAGIC, SEQ_NO, TYPE) and __IORW(MAGIC, SEQ_NO, TYPE) where the data flow will be from kernel space to user space and both ways respectively.
- The third argument is an untyped pointer to memory.  It's traditionally char *argp. Depending on the second argument, the third may or may not be present, e.g. if the second argument is SETFONT, the third argument can be the font name such as "Arial";
## Return value
- Usually, on success zero is returned.  A few ioctl() requests use
the return value as an output parameter and return a nonnegative
value on success.  
- On error, -1 is returned,
## Sample program
- To explain to you in detail the usage of the IOCTL function in the C programming language, we have made use of a simple C program. 
- We intend to open a specific device file from our system and write a random value to it in this program. After doing this, we also want to read a value from the very same file. You need to look at the code for this example to understand it more clearly.
- Personally i did'nt get much from the program now.
```
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <sys/ioctl.h>

  #define WR_VALUE _IOW('a', 'a', int32_t*)
  #define RD_VALUE _IOR('a', 'b', int32_t*)

  int main()
  {
    int fileDescriptor;
    int32_t val, num;
     printf("\nOpening the Driver\n");
     fileDescriptor=open("/dev/random", O_RDWR);
     if (fileDescriptor < 0)
     {
       printf("Unable to open the device file \n");
       return (0);
     }
     printf("Enter the value that you want to send \n");
     scanf("%d", &num);
     printf("Writing the value to the driver \n");
     ioctl(fileDescriptor, WR_VALUE, (int32_t *)&num);

     printf("Reading the value from the driver \n");
     ioctl(fileDescriptor, RD_VALUE, (int32_t *) &val);
     printf("The value is %d \n", val);

     printf("Closing the driver \n");
     close(fileDescriptor);
     return (0);
  }
```
- Out put
```
  mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out

  Opening the Driver
  Enter the value that you want to send 
  3
  Writing the value to the driver 
  Reading the value from the driver 
  The value is 32766 
  Closing the driver 
  mkaruvan@lab3r3s10 intro_to_allowed_functions % 
```
