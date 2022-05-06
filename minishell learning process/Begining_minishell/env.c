#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <termcap.h>
#include <readline/readline.h>
#include <string.h>
#include <readline/history.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

extern char **environ;

int main()
{
	char **s = environ;
	
	while (*s)
	{
		printf("%s \n", *s);
		s++;
	}
}