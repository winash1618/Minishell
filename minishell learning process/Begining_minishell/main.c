#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <termcap.h> 
#include <readline/readline.h>
#include <string.h>
#include <readline/history.h>

char *ft_readline(void)
{
	char *line= readline(">Enter a string: ");
	return (line);
}

void ft_clearscreen(void)
{
	char buf[1024];
	char *str;

	tgetent(buf, getenv("TERM"));
    str = tgetstr("cl", NULL);
	printf("%s", str);
	printf("");
}

int main()
{   
	char buf[1024];
    char *str;
    tgetent(buf, getenv("TERM"));
    str = tgetstr("cl", NULL);
	printf("%s", str);
	printf("");
	char *line;
	while (1)
	{
		line = ft_readline();
		
		
		if (!strcmp(line, "exit"))
			return (0);
		else if (!(strcmp(line, "")))
			;
		else if (!strcmp(line, "clear"))
			ft_clearscreen();
		else
			printf("You entered: %s\n", line);
		free (line);
	}
	return(0);
}


// Execution:
// gcc main.c -ltermcap -lreadline


// out put: if you do exit the program exits, if you do clear the screen is cleared.
// >Enter a string: hi
// You entered: hi
// >Enter a string: how are you
// You entered: how are you
// >Enter a string: 
// >Enter a string: exit
// mkaruvan@lab3r3s10 Begining_minishell % 
