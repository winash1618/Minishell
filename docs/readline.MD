# readline - get a line from a user with editing
## Usefull links
- https://www.man7.org/linux/man-pages/man3/readline.3.html#:~:text=readline%20will%20read%20a%20line,text%20of%20the%20line%20remains

## SYNOPSIS
```
       #include <stdio.h>
       #include <readline/readline.h>
       #include <readline/history.h>

       char *
       readline (const char *prompt);
```

## DESCRIPTION 
-  readline will read a line from the terminal and return it, using
       prompt as a prompt.  If prompt is NULL or the empty string, no
       prompt is issued.  The line returned is allocated with malloc(3);
       the caller must free it when finished.  The line returned has the
       final newline removed, so only the text of the line remains.
- 
