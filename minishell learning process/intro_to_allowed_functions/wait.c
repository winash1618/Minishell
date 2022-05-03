#include <sys/wait.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

// int main(int argc, char **argv)
// {
// 	pid_t pid;
// 	int res;

// 	pid = fork();
// 	if (pid == 0) {
// 		printf("child\n");
// 		exit(1);
// 	}
// 	pid = wait(&res);
// 	printf("raw res=%d\n", res);
// 	if (WIFEXITED(res))
// 		printf("exit status = %d\n", WEXITSTATUS(res));
// 	return 0;
// }

// int main(int argc, char *argv[])
// {
// 	pid_t cpid, w;
// 	int wstatus;

// 	cpid = fork();
// 	if (cpid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (cpid == 0) {            /* Code executed by child */
// 		printf("Child PID is %jd\n", (intmax_t) getpid());
// 		if (argc == 1)
// 			pause();                    /* Wait for signals */
// 		_exit(atoi(argv[1]));

// 	} else {                    /* Code executed by parent */
// 		do {
// 			w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
// 			if (w == -1) {
// 				perror("waitpid");
// 				exit(EXIT_FAILURE);
// 			}

// 			if (WIFEXITED(wstatus)) {
// 				printf("exited, status=%d\n", WEXITSTATUS(wstatus));
// 			} else if (WIFSIGNALED(wstatus)) {
// 				printf("killed by signal %d\n", WTERMSIG(wstatus));
// 			} else if (WIFSTOPPED(wstatus)) {
// 				printf("stopped by signal %d\n", WSTOPSIG(wstatus));
// 			} else if (WIFCONTINUED(wstatus)) {
// 				printf("continued\n");
// 			}
// 		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
// 		exit(EXIT_SUCCESS);
// 	}
// }
 
// int main()
// {
//     pid_t cpid;
//     if (fork()== 0)
//         exit(0);           /* terminate child */
//     else
//         cpid = wait(NULL); /* reaping parent */
//     printf("Parent pid = %d\n", getpid());
//     printf("Child pid = %d\n", cpid);
 
//     return 0;
// }

// int main()
// {
//     if (fork()== 0)
//         printf("HC: hello from child\n");
//     else
//     {
//         printf("HP: hello from parent\n");
//         wait(NULL);
//         printf("CT: child has terminated\n");
//     }
 
//     printf("Bye\n");
//     return 0;
// }

// void waitexample()
// {
//     int stat;
 
//     // This status 1 is reported by WEXITSTATUS
//     if (fork() == 0)
//         exit(1);
//     else
//         wait(&stat);
//     if (WIFEXITED(stat))
//         printf("Exit status: %d\n", WEXITSTATUS(stat));
//     else if (WIFSIGNALED(stat))
//         psignal(WTERMSIG(stat), "Exit signal");
// }
 
// // Driver code
// int main()
// {
//     waitexample();
//     return 0;
// }
 
// void waitexample()
// {
//     int i, stat;
//     pid_t pid[5];
//     for (i=0; i<5; i++)
//     {
//         if ((pid[i] = fork()) == 0)
//         {
//             sleep(1);
//             exit(100 + i);
//         }
//     }
 
//     // Using waitpid() and printing exit status
//     // of children.
//     for (i=0; i<5; i++)
//     {
//         pid_t cpid = waitpid(pid[i], &stat, 0);
//         if (WIFEXITED(stat))
//             printf("Child %d terminated with status: %d\n",
//                    cpid, WEXITSTATUS(stat));
//     }
// }
 
// // Driver code
// int main()
// {
//     waitexample();
//     return 0;
// }