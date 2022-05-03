#include <stdio.h>
#include <unistd.h>
 
// int main()
// {
// 	fork();
// 	printf("If the fork function is successful in creating a child process, I will print twice.\n");
// 	return 0;
// }

// int main()
// {
// 	int processID= fork();
// 	if(processID>0)
// 		printf("fork() returned a +ve value. This is the parent process, with ID: %d \n",getpid());
// 	else if(processID==0)
// 	{
// 		printf("fork() returned a 0 value. This is a newly created child process with ID: %d \n",getpid());
// 		printf("The parent process of this child process has the ID: %d\n",getppid());
// 	}
// 	else
// 		printf("fork() returned a -ve value, so the fork system called failed and the child process could not be created\n");
// 	printf("This is a single print statement. If the fork() system call was successful, both the parent and child process will run concurrently, and this statement will print twice.\n");
// 	return 0;
// }

int main()
{
	fork();
	fork();
	fork();
	printf("The fork function was called three times. I should print eight times.\n");
	return 0;
}