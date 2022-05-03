tips: If you’re familiar with man page conventions, you may have noticed that the termios functions are in man page section 3, which means that they’re provided by system libraries, and are not system calls.
# tcsetattr — set the parameters associated with the terminal
## Resources
- https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios/ ---------part 1------------
- https://blog.nelhage.com/2009/12/a-brief-introduction-to-termios-termios3-and-stty/ -------------part 2----------------
- https://c-for-dummies.com/blog/?p=4001
- https://www.cmrr.umn.edu/~strupp/serial.html
- https://www.cmrr.umn.edu/~strupp/vim-3.0.refcard.html ---- vim option nothing related-------
- https://man7.org/linux/man-pages/man3/tcsetattr.3p.html
- https://man7.org/linux/man-pages/man3/tcgetattr.3p.html
- https://www.setra.com/blog/what-is-baud-rate-and-what-cable-length-is-required-1 --------baud rate---------
- http://www.ece.northwestern.edu/local-apps/matlabhelp/techdoc/matlab_external/baudrate.html --------baud rate-----------
- http://embeddedguruji.blogspot.com/2019/01/serial-port-programming-part-2.html
## Synopsis
```
       #include <termios.h>

       int tcsetattr(int fildes, int optional_actions,
           const struct termios *termios_p);
```
## struct termios
```
  typedef unsigned long   tcflag_t;
  typedef unsigned char   cc_t;
  typedef unsigned long   speed_t;

  struct termios {
    tcflag_t        c_iflag;        /* input flags */
    tcflag_t        c_oflag;        /* output flags */
    tcflag_t        c_cflag;        /* control flags */
    tcflag_t        c_lflag;        /* local flags */
    cc_t            c_cc[NCCS];     /* control chars */
    speed_t         c_ispeed;       /* input speed */
    speed_t         c_ospeed;       /* output speed */
  };
```
## Description
- 

# tcgetattr — get the parameters associated with the terminal
## Synopsis
```
       #include <termios.h>

       int tcgetattr(int fildes, struct termios *termios_p);
```
## Description
- The tcgetattr() function shall get the parameters associated with
the terminal referred to by fildes and store them in the termios
structure referenced by termios_p.  The fildes argument is an
open file descriptor associated with a terminal.
- The termios_p argument is a pointer to a termios structure.
- The tcgetattr() operation is allowed from any process.
## Return value
- Upon successful completion, 0 shall be returned. 
- Otherwise, -1 shall be returned
