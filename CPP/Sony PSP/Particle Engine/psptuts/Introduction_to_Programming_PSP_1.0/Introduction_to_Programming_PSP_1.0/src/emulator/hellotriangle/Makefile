TARGET		= hellotriangle.elf
OBJS		= crt0.o hellotriangle.o
CC			= psp-gcc

SDKDIR		= c:/usr/local/sce/psp
INCDIR		= $(SDKDIR)/include
LIBDIR		= $(SDKDIR)/lib
CFLAGS		= -O2 -g -Wall -I$(INCDIR)
LFLAGS		= -O2 -g -Wall -mno-crt0 -L$(LIBDIR) \
			  -lgu -lemu -lm

.PHONY: all clean

all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

crt0.o: $(LIBDIR)/crt0.c
	$(CC) $(CFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	@-rm -f $(TARGET) *.o *~ *.bak

#hellotriangle.o: hellotriangle.c
