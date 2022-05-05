// #include        <stdio.h>
// #include        <curses.h>
// #include        <term.h>
// #include        <stdlib.h>

// int     main()
// {
//   const char *name;
//   char  *bp;
//   char  *term;
//   int   height;
//   int   width;

//   bp = malloc(sizeof(*bp));
//   name = "TERM";
//   if ((term = getenv(name)) == NULL)
//     return (1);
//   printf("My terminal is %s.\n", term);
//   tgetent(bp, term);
//   height = tgetnum("li");
//   width = tgetnum("co");
//   printf("H : %d\nL : %d\n", height, width);
//   free(bp);
//   return (0);
// }

//   #include        <stdio.h>
//   #include        <curses.h>
//   #include        <term.h>
//   #include        <stdlib.h>

//   int     main()
//   {
//     const char *name;
//     char  *bp;
//     char  *term;
//     int   flag;

//     bp = malloc(sizeof(*bp));
//     name = "TERM";
//     if ((term = getenv(name)) == NULL)
//       return (1);
//     printf("My terminal is %s.\n", term);
//     tgetent(bp, term);
//     flag = tgetflag("hs");
//     printf("flag hs = %d\n", flag);
//     free(bp);
//     return (0);
//   }

#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>   // getenv
#include <termcap.h>  // tgetent tgetstr

// char pc = 0;
// short ospeed = 9600;
// int fputchar(char c)
// {
// 	write(1, &c, 1);
// 	return (1);
// }
int main(void)
{
    char buf[1024];
    char *str;
    tgetent(buf, getenv("TERM"));
    str = tgetstr("wi", NULL);
	// tputs(str,10,&putchar);
	printf("%s", str);
    // fputs(str, stdout);
 	// printf("\033[1A\r\033[2K");
    return 0;
}
