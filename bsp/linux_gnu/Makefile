PROGNAME=oven$(oven)

CC=gcc
RKHSRCPATH=$(PWD)/../../rkh/source
PORTPATH= $(RKHSRCPATH)/portable/80x86/linux_st/gnu
PORTFILE=rkhport

DEMOSRCPATH=$(PWD)/../../oven/oven_$(oven)

DEFINE= -D__LNXGNU__ -D_BSD_SOURCE
CFLAGS = -ansi -Wall -I$(RKHSRCPATH)/include -I$(PWD) -I$(PORTPATH) -I$(DEMOSRCPATH) 
LDFLAGS	= -lc -pthread 

rkhobjects:=$(patsubst %.c,%.o,$(wildcard $(RKHSRCPATH)/*.c)) 
portobj:=$(patsubst %.c,%.o,$(wildcard $(PORTPATH)/*.c)) 
rkh:=$(patsubst $(RKHSRCPATH)/%, %,$(rkhobjects)) 

demoobj:=$(patsubst %.c,%.o,$(wildcard $(DEMOSRCPATH)/*.c)) 
demo:=$(patsubst $(DEMOSRCPATH)/%, %,$(demoobj)) 

objects:=$(patsubst %.c,%.o,$(wildcard *.c))

$(PROGNAME): $(objects) $(demoobj) $(rkhobjects) $(portobj) 
	@$(CC) -o $@ $(objects) $(rkh) $(demo) $(PORTFILE).o $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $(DEFINE) $<

clean: 
	/bin/rm -rf *.o *~ oven1 oven2 oven3 oven4 oven5 oven6

tags:
	ctags -R $(RKHSRCPATH) $(PWD)
