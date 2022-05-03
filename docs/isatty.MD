# isatty - test whether a file descriptor refers to a terminal
## Resources
- https://people.cs.rutgers.edu/~pxk/416/notes/c-tutorials/isatty.html#:~:text=the%20isatty%20library%20function%20takes,Otherwise%20it%20returns%200
- https://man7.org/linux/man-pages/man3/isatty.3.html
## Synopsis
```
       #include <unistd.h>
       int isatty(int fd);
```
## Description
- The isatty() function tests whether fd is an open file descriptor
referring to a terminal.
- In general, programs read from the standard input and write to the standard output, oblivious to whether the data is coming from or going out to a file or to the terminal. It is sometiems useful for a program to know whether it is interacting with a user or getting its data from a file.
- One common example is when a command interpreter has to issue prompts to the user. In that case, it is useful to know if the input is coming from the terminal or from a file or pipe. Another example is when the output might be formatted differently for a terminal, such as generating multi-column output or printing a header. The ls command is an example of such behavior, where it generates multi-column output on a terminal but single-column output for a file. One may argue that this is bad design since the user does not have direct feedback on what the output would look like when piped to another command or saved to a file.
## Return value
- isatty() returns 1 if fd is an open file descriptor referring to
a terminal.
- otherwise 0 is returned.
## Sample program
- This is a small program that tells you if the standard input and standard output are associated with a terminal.
```
  #include <stdlib.h>	/* needed for exit() */
  #include <unistd.h>	/* needed for isatty() */
  #include <stdio.h>	/* needed for printf() */

  int main(int argc, char **argv)
  {
    if (isatty(0))
      printf("the standard input is from a terminal\n");
    else
      printf("the standard input is NOT from a terminal\n");
    if (isatty(1))
      printf("the standard output is to a terminal\n");
    else
      printf("the standard output is NOT to a terminal\n");
    exit(0);
  }
```
- Compile this program via:
```
  gcc -o isatty isatty.c
```
- Outputs
  - if you run ./isatty
  ```
    the standard input is from a terminal
    the standard output is to a terminal
  ```
  - If you replace the standard input with the null device: run ./isatty </dev/null
  ```
    the standard input is NOT from a terminal
    the standard output is to a terminal
  ```
  - If you replace the standard output with a pipe to the cat command: run ./isatty |cat
  ```
      the standard input is from a terminal
      the standard output is NOT to a terminal
  ```

