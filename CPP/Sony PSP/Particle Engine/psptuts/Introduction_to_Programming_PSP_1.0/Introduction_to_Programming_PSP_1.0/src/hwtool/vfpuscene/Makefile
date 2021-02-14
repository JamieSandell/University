TARGET		= vfpu3dscene
OBJS			= vfpu3dscene.o

SDK_TOP		= /usr/local/psp/devkit
INCDIR		= $(SDK_TOP)/include
LIBDIR		= $(SDK_TOP)/lib

DBGFLAG		= -g
OPTFLAG		= -O2
CFLAGS		= -Wall $(DBGFLAG) $(OPTFLAG) -I$(INCDIR)
ASFLAGS		= $(DBGFLAG)
LDFLAGS		= $(DBGFLAG) -L$(LIBDIR)
LDLIBS		=  -lgu -lgum -lm -lvfpu -lstdc++ -lsupc++ 
LOADLIBES	=  $(LIBDIR)/ctrl_stub.a
LOADLIBES	+= $(LIBDIR)/display_stub.a
LOADLIBES	+= $(LIBDIR)/ge_user_stub.a

all:	$(TARGET).prx $(TARGET).elf

clean:
	rm -f $(TARGET).prx $(TARGET).elf *.o *~ *.bak

$(TARGET).prx: $(OBJS)
	$(LINK.c) $^ $(LDLIBS) $(LOADLIBES) -startfiles -o $@

$(TARGET).elf: $(OBJS)
	$(LINK.c) $^ $(LDLIBS) $(LOADLIBES) -zgenelf -o $@

#----------- rules --------------
-include PathDefs
PathDefs:
	psp-path-setup > PathDefs || (rm -f PathDefs ; exit 1)
