CC=gcc
CFLAGS=-Wall -DEXFILES_BASE="\"$(shell pwd)\""

LIB=libnss_exfiles.so.2

all: clean devel

devel: nss_exfiles.o
	$(CC) $(CFLAGS) -shared -o $(LIB) -Wl,-soname,$(LIB) nss_exfiles.o

testdevel: nss_exfiles.o testdevel.o
	$(CC) $(CFLAGS) $^ -o testdevel

clean: 
	-rm $(LIB) *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.SUFFIXES:
.SUFFIXES: .cpp .o .h

