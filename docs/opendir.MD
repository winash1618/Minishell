# opendir - open a directory
## Resources
- https://man7.org/linux/man-pages/man3/opendir.3.html
- https://firstlawcomic.com/what-is-a-directory-stream-in-c/
- https://stackoverflow.com/questions/3554120/open-directory-using-c
- https://man7.org/linux/man-pages/man3/readdir.3.html
- https://stackoverflow.com/questions/20265328/readdir-beginning-with-dots-instead-of-files
- https://man7.org/linux/man-pages/man3/closedir.3.html
## Synopsis
```
       #include <sys/types.h>
       #include <dirent.h>

       DIR *opendir(const char *name);
```
- Let's look what's inside DIR structure.
```
       /* structure describing an open directory. */
       typedef struct {
              int	__dd_fd;	/* file descriptor associated with directory */
              long	__dd_loc;	/* offset in current buffer */
              long	__dd_size;	/* amount of data returned */
              char	*__dd_buf;	/* data buffer */
              int	__dd_len;	/* size of data buffer */
              long	__dd_seek;	/* magic cookie returned */
              __unused long	__padding; /* (__dd_rewind space left for bincompat) */
              int	__dd_flags;	/* flags for readdir */
              __darwin_pthread_mutex_t __dd_lock; /* for thread locking */
              struct _telldir *__dd_td; /* telldir position recording */
       } DIR;
```
## Description
- The opendir() function opens a directory stream corresponding to
the directory name, and returns a pointer to the directory
stream.  The stream is positioned at the first entry in the
directory.
- Directory stream : An object to iterate over the entries in a directory.
## Return value
- The opendir() functions return a pointer to the directory stream.  
- On error, NULL is returned.
# readdir - read a directory
## Synopsis
```
       #include <dirent.h>

       struct dirent *readdir(DIR *dirp);
```
## Description
- The readdir() function returns a pointer to a dirent structure
representing the next directory entry in the directory stream
pointed to by dirp.  It returns NULL on reaching the end of the
directory stream or if an error occurred.
- The dirent structure is defined as
follows:

```
       struct dirent {
              ino_t d_ino;                    /* file number of entry */
              __uint16_t d_reclen;            /* length of this record */
              __uint8_t  d_type;              /* file type, see below */
              __uint8_t  d_namlen;            /* length of string in d_name */
              char d_name[__DARWIN_MAXNAMLEN + 1];    /* name must be no longer than this */
       };
```
## Return value
- On success, readdir() returns a pointer to a dirent structure. 
- On failure, If the end of the directory stream is reached or some error occured, NULL is returned
# closedir - close a directory
## Synopsis
```
       #include <sys/types.h>
       #include <dirent.h>

       int closedir(DIR *dirp);
```
## Description
- The closedir() function closes the directory stream associated
with dirp.  A successful call to closedir() also closes the
underlying file descriptor associated with dirp.  The directory
stream descriptor dirp is not available after this call.
## Return value
- The closedir() function returns 0 on success.  
- On error, -1 is returned.
## Sample program
- A C program to illustrate the working of opendir and readdir function
```
  #include <stdio.h>
  #include <dirent.h>

  int main (int argc, char *argv[])
  {
    struct dirent *pDirent;
    DIR *pDir;

    // Ensure correct argument count.

    if (argc != 2) {
      printf ("Usage: testprog <dirname>\n");
      return 1;
    }

    // Ensure we can open directory.

    pDir = opendir (argv[1]);
    if (pDir == NULL) {
      printf ("Cannot open directory '%s'\n", argv[1]);
      return 1;
    }

    // Process each entry.

    while ((pDirent = readdir(pDir)) != NULL) {
      printf ("[%s]\n", pDirent->d_name);
    }

    // Close directory and exit.

    closedir (pDir);
    return 0;
  }
```
- Out put 
```
mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out ~/Desktop 
[.]
[..]
[.DS_Store]
[.git]
[42-ValgrindContainer]
[alal]
[fc]
[knoree.png]
[mini]
[minitalk]
[philo]
[push_swap]
[push_swap_ay]
[pushswap]
[Relocated Items]
[Screen Shot 2022-04-24 at 4.48.02 PM.png]
[test]
[Visual Studio Code.app]
mkaruvan@lab3r3s10 intro_to_allowed_functions
```
- Inorder to . & .. from the output 
```
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main()
{
    DIR *dir;
    struct dirent *dp;
    char * file_name;
    dir = opendir(".");
    while ((dp=readdir(dir)) != NULL) {
        printf("debug: %s\n", dp->d_name);
        if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
        {
            // do nothing (straight logic)
        } else {
            file_name = dp->d_name; // use it
            printf("file_name: \"%s\"\n",file_name);
        }
    }
    closedir(dir);
    return 0;
}
```
- Out put
```
mkaruvan@lab3r3s10 intro_to_allowed_functions % ./a.out      
debug: .
debug: ..
debug: a.out
file_name: "a.out"
debug: access.c
file_name: "access.c"
debug: chdir.c
file_name: "chdir.c"
debug: dup.c
file_name: "dup.c"
debug: execve.c
file_name: "execve.c"
debug: fork.c
file_name: "fork.c"
debug: getcwd.c
file_name: "getcwd.c"
debug: myecho.c
file_name: "myecho.c"
debug: opendir.c
file_name: "opendir.c"
debug: pipe.c
file_name: "pipe.c"
debug: readline.c
file_name: "readline.c"
debug: rl_history.c
file_name: "rl_history.c"
debug: stat.c
file_name: "stat.c"
debug: unlink.c
file_name: "unlink.c"
debug: wait.c
file_name: "wait.c"
```
