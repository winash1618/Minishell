// #include <stdio.h>
//   #include <string.h>
//   #include <errno.h>

//   int main () {
//      FILE *fp;

//      fp = fopen("file.txt","r");
//      if( fp == NULL ) {
//         printf("Error: %s\n", strerror(errno));
//      }

//      return(0);
//   }

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
