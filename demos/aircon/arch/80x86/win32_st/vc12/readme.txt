/**
\image html rkh_bunner.jpg

Running Oven RKH demo on Windows platform
This is a guide to how to compile and run demos.

<STRONG>Folder tree</STRONG>

\code
\-win32vc\
    assert.c	     - RKH assertion resolution.
    bsp.h		     - Board support package header file.
    bsp_oven.c	     - Board support package source file.
    getopt.c/h	     - minimal getopt facility.
    hook.c	         - RKH hooks resolution.
    readme.txt	     - This guide file.
    trace_io.c	     - Trace facility IO interface.
    trace_io_cfg.h   - Trace configuration file.
    trace_io_tcp.c/h - TCP socket for sending trace info source file.
	prj\
		oven.sln - Visual Studio C++ 2010 Solution with all projects demos
	Makefile	 - makefile file.
\endcode

Running demos:
  - Before to run any demo, trazer client must be started: 
	trazer -t 6602

*/
