/**
\image html rkh_bunner.jpg

Running Oven RKH demo on Windows platform
This is a guide to how to compile and run demos.

<STRONG>Folder tree</STRONG>

\code
\-win32vc08\
    bsp.c		 - Board support package source file.
    bsp.h		 - Board support package header file.
    tcptrc.c	 - TCP socket for sending trace info source file.
    tcptrc.c	 - TCP socket for sending trace info header file.
    readme.txt	 - This guide file.
	prj\
		oven.sln - Visual Studio C++ 2010 Solution with all projects demos
	Makefile	 - makefile file.
\endcode

Running demos:
  - Before to run any demo, trazer client must be started: 
	trazer -t 6602

*/
