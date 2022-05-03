#include <stdlib.h>	/* needed to define exit() */
#include <unistd.h>	/* needed to define getpid() */
#include <stdio.h>	/* needed for printf() */

int main(int argc, char **argv) {
	char *args[] = {"ls", "-aF", "/", 0};	/* each element represents a command line argument */
	char *env[] = { 0 };	/* leave the environment list null */

	printf("About to run /bin/ls\n");
	execve("/bin/ls", args, env);
	perror("execve");	/* if we get here, execve failed */
	exit(1);
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main(int argc, char *argv[])
// {
// 	char *newargv[] = { NULL, "hello", "world", NULL };
// 	char *newenviron[] = { NULL };

// 	if (argc != 2) {
// 		fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
// 		exit(EXIT_FAILURE);
// 	}

// 	newargv[0] = argv[1];

// 	execve(argv[1], newargv, newenviron);
// 	perror("execve");   /* execve() returns only on error */
// 	exit(EXIT_FAILURE);
// }