#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>   // getenv
#include <termcap.h> 
#include <readline/readline.h>
#include <string.h>
#include <readline/history.h>

// #define SIZE 15
// void child(int p1[])
// {
// 	write(p1[1],readline("Enter something: "), SIZE);
// 	close(p1[1]);
// }

// void parent(int p1[], char inbuf[])
// {
// 	printf("This is from parent\n");
// 	read(p1[0], inbuf, SIZE);
// 	printf("%s \n", inbuf);
// }

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
	// char inbuf[SIZE];
    char *str;
	// int p1[2];
	// if (pipe(p1) == -1)
	// {
	// 	printf("Print Error \n");
	// }
    tgetent(buf, getenv("TERM"));
    str = tgetstr("cl", NULL);
	printf("%s", str);
	printf("");
	// fflush(stdout);
	// int pid = fork();
	// if (pid == -1)
	// {
	// 	printf("Error forking, Please try again \n");
	// }
	// else if (pid == 0)
	// {
	// 	child(p1);
	// }
	// else
	// {
	// 	wait (NULL);
	// 	parent(p1, inbuf);
	// 	while (1)
	// 	{

	// 	}
	// }
	char *line;
	while (1)
	{
		line = ft_readline();
		printf("You entered: %s\n", line);
		free (line);
		if (!strcmp(line, "exit"))
			exit (1);
		else if (!strcmp(line, "clear"))
			ft_clearscreen();
	}
	return(0);
}