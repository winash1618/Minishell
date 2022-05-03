# opendir - open a directory
## Resources
- https://man7.org/linux/man-pages/man3/opendir.3.html
- https://firstlawcomic.com/what-is-a-directory-stream-in-c/
- https://stackoverflow.com/questions/3554120/open-directory-using-c
## Synopsis
```
       #include <sys/types.h>
       #include <dirent.h>

       DIR *opendir(const char *name);
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
## Sample program
- A C program to illustrate the working of opendir function
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



