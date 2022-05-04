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
       
       int tgetent(char *bp, const char *name);
       int tgetflag(const char *id);
       int tgetnum(const char *id);
       char *tgetstr(const char *id, char **area);
       char *tgoto(const char *cap, int col, int row);
       int tputs(const char *str, int affcnt, int (*putc)(int));
```
## Description

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

