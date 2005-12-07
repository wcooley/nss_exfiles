CC	=	gcc
CFLAGS	=	-Wall -DEXFILES_BASE="\"$(shell pwd)\""
LIB_SO	=	libnss_exfiles.so.2
LEX	=	lex
YACC	=	bison -d
PROG	=	exfiles_conf

all: clean devel

exfiles_conf: exfiles_conf.tab.o lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^ -ll

lex.yy.o: lex.yy.c exfiles_conf.tab.h
	$(CC) $(CFLAGS) -c $< 

lex.yy.c: exfiles_conf.l
	$(LEX) $<

exfiles_conf.tab.h exfiles_conf.tab.c: exfiles_conf.y
	$(YACC) $<

exfiles_conf.tab.o: exfiles_conf.tab.c
	$(CC) $(CFLAGS) -c $<

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

