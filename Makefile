CC=gcc
CFLAGS=-Wall -static -g -DEXFILES_BASE="\"$(shell pwd)\""

LIB=libnss_exfiles.so.2

all: clean devel

devel: nss_exfiles.o split.o
	$(CC) $(CFLAGS) -shared -o $(LIB) -Wl,-soname,$(LIB) nss_exfiles.o split.o

testdevel: nss_exfiles.o testdevel.o
	$(CC) $(CFLAGS) $^ -o testdevel

clean: 
	-rm $(LIB) *.o

lex.yy.c: exfiles_conf.l
	lex $<

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.SUFFIXES:
.SUFFIXES: .cpp .o .h

