# unlink - delete a name and possibly the file it refers to
## Resources
- https://man7.org/linux/man-pages/man2/unlink.2.html
- https://linuxhint.com/unlink-system-call-in-c/
## Synopsis
```
       #include <unistd.h>
       int unlink(const char *pathname);
```
## Description
- unlink() deletes a name from the filesystem.  If that name was
the last link to a file and no processes have the file open, the
file is deleted and the space it was using is made available for
reuse.
- If the name was the last link to a file but any processes still
have the file open, the file will remain in existence until the
last file descriptor referring to it is closed.
- If the name referred to a symbolic link, the link is removed.
- If the name referred to a socket, FIFO, or device, the name for
it is removed but processes which have the object open may
continue to use it.
## Return value
- On success, zero is returned.  
- On error, -1 is returned.
## Sample program
-- We have defined and included certain input-output header libraries and Posix extensions as well. 
Then we have initialized the main method to declare file descriptor “fd”.   
Character type array has been used to get the contents of a file “new.txt”. 
An “if” statement has been used to check the create file error. 
If the file descriptor finds that the file has a link count of less than 0, it may display an error message. 
The else statement has been used to close the file descriptor. 
If the file has the unlink count not equal to 0, it will display the error message.
```
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
```
- Out put
```
mkaruvan@lab3r3s10 intro_to_allowed_functions % ls
a.out           chdir.c         getcwd.c        readline.c      stat.c          wait.c
access.c        fork.c          new.txt         rl_history.c    unlink.c
mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out
mkaruvan@lab3r3s10 intro_to_allowed_functions % ls     
a.out           chdir.c         getcwd.c        rl_history.c    unlink.c
access.c        fork.c          readline.c      stat.c          wait.c
mkaruvan@lab3r3s10 intro_to_allowed_functions %
```
- Note: we can do the same thing as shown in the above program by calling open() function.
