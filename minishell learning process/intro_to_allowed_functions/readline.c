#include<stdlib.h>
    #include<stdio.h>
    #include<readline/readline.h>
    #include<readline/history.h>

    int main(){

       char* line;

       line = readline("enter a string:  ");  // readline allocates space for returned string
       if(line != NULL) { 
           printf("You entered: %s\n", line);
           free(line);   // but you are responsible for freeing the space
       }
    }