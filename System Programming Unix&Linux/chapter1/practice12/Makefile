# Makefile

CC=gcc
CFLAGS=
OBJS=ch1_3_main.o subnum.o
LIBS=
all : sub.out

sub.out : $(OBJS)
	$(CC) $(CFLAGS) -o sub.out $(OBJS) $(LIBS)

ch1_3_main.o : ch1_3_main.c
	$(CC) $(CFLAGS) -c ch1_3_main.c
	
subnum.o : subnum.c
		$(CC) $(CFLAGS) -c subnum.c
		
clean:
	rm -f $(OBJS) sub.out *.o core
	

