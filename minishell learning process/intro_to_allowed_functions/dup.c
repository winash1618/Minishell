//-------------------dup--------------------------//

// // CPP program to illustrate dup() 
// #include<stdio.h>
// #include <unistd.h>
// #include <fcntl.h>
  
// int main()
// {
//     // open() returns a file descriptor file_desc to a 
//     // the file "dup.txt" here"
  
//     int file_desc = open("dup.txt", O_WRONLY | O_APPEND | O_CREAT);
      
//     if(file_desc < 0)
//         printf("Error opening the file\n");
      
//     // dup() will create the copy of file_desc as the copy_desc
//     // then both can be used interchangeably.
  
//     int copy_desc = dup(file_desc);
          
//     // write() will write the given string into the file
//     // referred by the file descriptors
  
//     write(copy_desc,"This will be output to the file named dup.txt\n", 46);
          
//     write(file_desc,"This will also be output to the file named dup.txt\n", 51);
      
//     return 0;
// }

//------------------------------------------------//

//-----------------------dup2()-------------------//


// CPP program to illustrate dup2() 
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main()
{
    int file_desc = open("tricky.txt",O_RDWR | O_APPEND | O_CREAT);
      
    // here the newfd is the file descriptor of stdout (i.e. 1)
    dup2(file_desc, 1) ; 
          
    // All the printf statements will be written in the file
    // "tricky.txt"
    printf("I will be printed in the file tricky.txt\n");
      
return 0;
}

//------------------------------------------------//