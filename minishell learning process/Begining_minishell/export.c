// #include <stdio.h>
// #include <unistd.h>
// #include <curses.h>
// #include <term.h>
// #include <stdlib.h>
// #include <termcap.h>
// #include <readline/readline.h>
// #include <string.h>
// #include <readline/history.h>
// #include <fcntl.h>
// #include<sys/types.h>
// #include<sys/stat.h>


// int main ()
// {
// 	char *const argv = { "-c", "env", 0 };
// 	char *const env = { "PATH=/bin", "var=5", 0 };

// 	execve("/bin/bash", argv, env);

// }

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *argv[] = { "/bin/sh", "-c", "export", 0 };
	char *envp[] =
	{
		"TZ=UTC0",
		0
	};
	execve(argv[0], &argv[0], envp);
	return -1;
}