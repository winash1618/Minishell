# readline - get a line from a user with editing
## tips
-To use readline, you need to include readline header files and explicitly link with the readline library:
```
       $ gcc -o myprog  myprog.c -lreadline
```
## Introduction
- readline is a GNU library for reading in user input. It has support for all kinds of line editing capabilities that the user can use to edit the input line. For example, the user can move the curser to different positions in the line, and modify parts of the input string. See the readline man page and the readline homepage for complete information about the readline library: [GNU readline homepage](http://tiswww.case.edu/php/chet/readline/rltop.html)
- One very nice feature of readline is that it mallocs up the space for the returned string. Thus, a program can easily support reading in any sized user input string by simply calling readline. Thus, even if you don't care about any of the line editing features of readline, it is still a handy way to read in user input.
## Usefull links
- https://www.man7.org/linux/man-pages/man3/readline.3.html#:~:text=readline%20will%20read%20a%20line,text%20of%20the%20line%20remains
- http://tiswww.case.edu/php/chet/readline/rltop.html
- https://www.cs.swarthmore.edu/~newhall/unixhelp/C_cool_utils.html ----cool page------
- https://www.cs.swarthmore.edu/~newhall/unixlinks.html ------not related but way cooler-------

## Synopsis
```
       #include <stdio.h>
       #include <readline/readline.h>
       #include <readline/history.h>

       char *
       readline (const char *prompt);
```

## Description 
- readline will read a line from the terminal and return it, using
       prompt as a prompt.  If prompt is NULL or the empty string, no
       prompt is issued.  The line returned is allocated with malloc(3);
       the caller must free it when finished.  The line returned has the
       final newline removed, so only the text of the line remains.
## Return values
- readline returns the text of the line read.  A blank line returns
       the empty string.  If EOF is encountered while reading a line,
       and the line is empty, NULL is returned.  If an EOF is read with
       a non-empty line, it is treated as a newline.
       
## Sample Program
- Here is a very simple example program:
```
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
```
- As you run this, type in a line and before you hit ENTER try some of these commands to change the input string:
```
    CNTRL-a   move curser to begining of input string
    CNTRL-e   move curser to end of input string
    CNTRL-b   move curser back one character
    CNTRL-f   move curser forward one character
    CNTRL-d   delete the character under the curser
    CNTRL-k   kill the string from the curser to the end of the line
    CNTRL-l   clear the screen and re-print the prompt and input string at the top
```
- output:
```
       enter a string:  jhs
       You entered: jhs
```
