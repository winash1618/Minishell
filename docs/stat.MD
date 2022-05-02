# stat, fstat, lstat - get file status
## Resources
- https://kb.iu.edu/d/abbe "Explains about what is symbolic links."
- https://www.futurelearn.com/info/courses/linux-for-bioinformatics/0/steps/201767#:~:text=A%20symlink%20is%20a%20symbolic,directory%20in%20any%20file%20system
- https://www.geeksforgeeks.org/soft-hard-links-unixlinux/
- https://man7.org/linux/man-pages/man2/lstat.2.html - man page on stat, fstat, lstat
## Synopsis
```
       #include <sys/stat.h>

       int stat(const char *restrict pathname,
                struct stat *restrict statbuf);
       int fstat(int fd, struct stat *statbuf);
       int lstat(const char *restrict pathname,
                struct stat *restrict statbuf);
```
## Description
- These functions return information about a file, in the buffer
pointed to by statbuf.  No permissions are required on the file
itself, but—in the case of stat(), and lstat() — execute
(search) permission is required on all of the directories in
pathname that lead to the file.
- lstat() is identical to stat(), except that if pathname is a
symbolic link, then it returns information about the link itself,
not the file that the link refers to.
- fstat() is identical to stat(), except that the file about which
information is to be retrieved is specified by the file
descriptor fd.
## Return value
- On success, zero is returned.  
- On error, -1 is returned


