# Minishell:
This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.
## tips
- echo $PATH (you can do echo to display what is value of environment variable)
- if you forgot what meta character is read [this](https://en.wikipedia.org/wiki/Metacharacter).
- print all the environment varialbles. read [this](https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c).
- Global variable 
- https://www.quora.com/We-can-access-global-variables-in-other-files-Why-cant-we-access-static-global-variables-in-other-files
- A global variable is a variable that is defined outside all functions and available to all functions. These variables are unaffected by scopes and are always available, which means that a global variable exists until the program ends. It is possible to create a global variable in one file and access it from another file. In order to do this, the variable must be declared in both files, but the keyword extern must precede the "second" declaration. global static variable is one that can only be accessed in the file where it is created. This variable is said to have file scope. So if the global variable is static it can not be accessed outside the file.
## resources:
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- https://github.com/anolivei/Minishell42
- https://tiswww.case.edu/php/chet/readline/history.html#SEC12
- http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/ ----------------explore------------------
- http://www.iakovlev.org/index.html?p=1169&m=1&l1=5 ---explore---
- https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e
- http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/unix_lecture_notes.php
- https://medium.com/@sahmaanwar61/how-i-made-a-miniaturized-unix-shell-using-c-fbd69ca7f584
- https://github.com/kalpishs/Unix-Shell-Implementation-in-C/blob/master/shell.c
- https://viewsourcecode.org/snaptoken/kilo/index.html ----------make your own text editor walk through---------
- https://brennan.io/2015/01/16/write-a-shell-in-c/
- https://xesoa.com/wp-content/uploads/2014/04/APUE-3rd.pdf
- https://www.quora.com/What-are-some-good-tutorials-for-writing-a-shell-in-C
- https://web.stonehill.edu/compsci/CS314/Assignments/Assignment2.pdf
- https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/?utm_source=linuxnewssite.com
- http://metalab.uniten.edu.my/~abdrahim/csnb334(xcvb)/ll_.pdf
## Introduction to allowed functions:
- [readline](docs/readline.MD)
- [access](docs/access.MD)
- [fork](docs/fork.MD)
- [wait](docs/wait.MD)
- [getcwd](docs/getcwd.MD)
- [chdir](docs/chdir.MD)
- [stat, fstat, lsata](docs/stat.MD)
- [unlink](docs/unlink.MD)
- [execve](docs/execve.MD)
- [dup & dup2](docs/dup.MD)
- [pipe](docs/pipe.MD)
- [opendir, readdir & closedir](docs/opendir.MD)
- [strerror & perror](docs/errors.MD)
- [isatty](docs/isatty.MD)
- [ttyname & ttyslot](docs/tty.MD)
- [ioctl](docs/ioctl.MD)
- [getenv](docs/getenv.MD)
- [tcsetattr & tcgetattr](docs/tcattr.MD)
- [tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs](docs/tget.MD)
