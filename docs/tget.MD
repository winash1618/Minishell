## Resources
- badprog.com/unix-gnu-linux-system-calls-using-tgetnum
- https://man7.org/linux/man-pages/man5/termcap.5.html
- https://www.badprog.com/unix-gnu-linux-system-calls-using-tgetflag
- https://www.gnu.org/software/termutils/manual/termcap-1.3/html_node/termcap_1.html#SEC1

# tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs - curses emulation of termcap
## Synopsis
```
       #include <curses.h>
       #include <term.h>
       
       extern char PC;
       extern char * UP;
       extern char * BC;
       extern unsigned ospeed;
       
       int tgetent(char *bp, const char *name);
       int tgetflag(const char *id);
       int tgetnum(const char *id);
       char *tgetstr(const char *id, char **area);
       char *tgoto(const char *cap, int col, int row);
       int tputs(const char *str, int affcnt, int (*putc)(int));
```
## Description
- This function finds the description and remembers it internally so that you can interrogate it about specific terminal capabilities ith tgetnum, tgetstr or tgetflag. The argument termtype is a string which is the name for the type of terminal to look up. Usually you would obtain this from the environment variable TERM using getenv ("TERM"). With the Unix version of termcap, you must allocate space for the description yourself and pass the address of the space as the argument buffer. There is no way you can tell how much space is needed, so the convention is to allocate a buffer 2048 characters long and assume that is enough.
- Each piece of information recorded in a terminal description is called a capability. Each defined terminal capability has a two-letter code name and a specific meaning. For example, the number of columns is named 'co'.
- Once you have found the proper terminal description with tgetent, your application program must interrogate it for various terminal capabilities. You must specify the two-letter code of the capability whose value you seek.
- Capability values can be numeric, boolean (capability is either present or absent) or strings. Any particular capability always has the same value type; for example, 'co' always has a numeric value, while 'am' (automatic wrap at margin) is always a flag, and 'cm' (cursor motion command) always has a string value. The documentation of each capability says which type of value it has.
- There are three functions to use to get the value of a capability, depending on the type of value the capability has. Here are their declarations in ANSI C:
       - tgetnum : Use tgetnum to get a capability value that is numeric. The argument name is the two-letter code name of the capability. If the capability is present, tgetnum returns the numeric value (which is nonnegative). If the capability is not mentioned in the terminal description, tgetnum returns -1.
       - tgetflag : Use tgetflag to get a boolean value. If the capability name is present in the terminal description, tgetflag returns 1; otherwise, it returns 0.
       - tgetstr : Use tgetstr to get a string value. It returns a pointer to a string which is the capability value, or a null pointer if the capability is not present in the terminal description. You need to provide the space yourself for the string, this is the only method supported by the Unix version of termcap.
- Before starting to output commands to a terminal using termcap, an application program should do two things: 
       - Initialize various global variables which termcap library output functions refer to. These include PC and ospeed for padding and UP and BC for cursor motion.
       - Tell the kernel to turn off alteration and padding of horizontal-tab characters sent to the terminal.
- Use the termcap function tputs to output a string containing an optional padding spec The function tputs strips off and decodes the padding spec, outputs the rest of the string, and then outputs the appropriate padding. Here is its declaration in ANSI C:
```
char PC;
short ospeed;

int tputs (char *string, int nlines, int (*outfun) ());
```
- For the 'cm' capability, since tgoto has a special feature to avoid problems with null characters, tabs and newlines on certain old terminal types that use '%.' encoding for that capability.
- There are three arguments, the terminal description's 'cm' string and the two cursor position numbers; tgoto computes the parametrized string in an internal static buffer and returns the address of that buffer. The next time you use tgoto the same buffer will be reused.
## Return value
- The return value of tgetent is -1 if there is some difficulty accessing the data base of terminal types, 0 if the data base is accessible but the specified type is not defined in it, and some other value otherwise.
## Sample program
- Let's see an example of the tgetflag() function with to show if our terminal has a status line (hs):
```
  #include        <stdio.h>
  #include        <curses.h>
  #include        <term.h>
  #include        <stdlib.h>

  int     main()
  {
    const char *name;
    char  *bp;
    char  *term;
    int   flag;

    bp = malloc(sizeof(*bp));
    name = "TERM";
    if ((term = getenv(name)) == NULL)
      return (1);
    printf("My terminal is %s.\n", term);
    tgetent(bp, term);
    flag = tgetflag("hs");
    printf("flag hs = %d\n", flag);
    free(bp);
    return (0);
  }
```
- Out put : 
```
  mkaruvan@lab3r3s10 intro_to_allowed_functions % gcc tget.c -lncurses
  mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out             
  My terminal is xterm-256color.
  flag hs = 0
  mkaruvan@lab3r3s10 intro_to_allowed_functions % 
```

- Let's see an example of the tgetnum() function with the "TERM" variable and its height and width:
```
  #include        <stdio.h>
  #include        <curses.h>
  #include        <term.h>
  #include        <stdlib.h>

  int     main()
  {
    const char *name;
    char  *bp;
    char  *term;
    int   height;
    int   width;

    bp = malloc(sizeof(*bp));
    name = "TERM";
    if ((term = getenv(name)) == NULL)
      return (1);
    printf("My terminal is %s.\n", term);
    tgetent(bp, term);
    height = tgetnum("li");
    width = tgetnum("co");
    printf("H : %d\nL : %d\n", height, width);
    free(bp);
    return (0);
  }
```
- Out put : Do not forget to use the -lncurses library when you compile. This will print terminal height and width in number of lines and columns currently visible. You can change the out put by changing the window size.
```
  mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out             
  My terminal is xterm-256color.
  H : 31
  L : 107
  mkaruvan@lab3r3s10 intro_to_allowed_functions %
```
- Now lets look at how we can clear the terminal screen when using tgetent and tgetstr.
```
  #include <curses.h>
  #include <term.h>
  #include <stdio.h>
  #include <stdlib.h>   // getenv
  #include <termcap.h>  // tgetent tgetstr
  int main(void)
  {
      char buf[1024];
      char *str;
      tgetent(buf, getenv("TERM"));
      str = tgetstr("cl", NULL);
      //printf("%s", str); behave same like fputs
      fputs(str, stdout);
      return 0;
  }
```
- Compile the above code with -ltermcap.
- Out put will clear the screen.

