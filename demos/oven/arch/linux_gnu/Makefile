PROGNAME=oven$(oven)

CC=gcc
RKHSRCPATH=$(PWD)/../../../../rkh/source
PORTPATH= $(RKHSRCPATH)/portable/80x86/linux_st/gnu
PORTFILE=rkhport

OVEN1SRCPATH=$(PWD)/../../oven1
OVEN2SRCPATH=$(PWD)/../../oven2
OVEN3SRCPATH=$(PWD)/../../oven3
OVEN4SRCPATH=$(PWD)/../../oven4

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

oven1: $(objects) $(demoobj) $(rkhobjects) $(portobj) 
	@$(CC) -o $@ $(objects) $(rkh) $(demo) $(PORTFILE).o $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $(DEFINE) $<

clean: 
	/bin/rm -rf *.o *~

tags:
	ctags -R $(RKHSRCPATH) $(PWD)

print:
	@echo $(OVEN1SRCPATH)
