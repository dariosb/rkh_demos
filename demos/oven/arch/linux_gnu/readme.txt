/**
\image html rkh_bunner.jpg

Running Oven RKH demo on Linux platform
This is a guide to how to compile and run demos.

<STRONG>Folder tree</STRONG>

\code
\-linux_gnu\
    bsp.c	- Board support package source file.
    bsp.h	- Board support package header file.
    tcptrc.c	- TCP socket for sending trace info source file.
    tcptrc.c	- TCP socket for sending trace info header file.
    readme.txt	- This guide file.
    Makefile	- makefile file.
    buildall	- Builds all oven1..6 demos
\endcode

Running demos:
  - Before to run any demo, trazer client must be started.
  - Use trazer -t 6602 to run trazer on TCP socket at 6602 port.
*/
