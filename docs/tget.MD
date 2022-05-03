## Resources
- badprog.com/unix-gnu-linux-system-calls-using-tgetnum
- https://man7.org/linux/man-pages/man5/termcap.5.html
- https://www.badprog.com/unix-gnu-linux-system-calls-using-tgetflag


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
