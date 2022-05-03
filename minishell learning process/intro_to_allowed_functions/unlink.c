#define _POSIX_SOURCE
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>

int main()
{
	int fd;
	char f[] = "new.txt";
	if ((fd =creat(f, S_IWUSR)) < 0)
	{
		perror ("creat() error");
	}
	else
	{
		close (fd);
		if (unlink(f) != 0)
			perror ("unlink() error");
	}
}