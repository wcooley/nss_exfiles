CC		= gcc
#CFLAGS		= -Wall -g -I../cunit-0.7.5/src/libcunit/ -I../src
CFLAGS		= -Wall -I../src


test_strlist: test_strlist.o ../src/strlist.o
	$(CC) $(CFLAGS)  -o $@ $^ /usr/lib/libcheck.a
	./$@

libtest_string_list.so: test_string_list.c
	$(CC) $(CFLAGS) -shared -o $@ -Wl,-soname,$@ $<

%.so: %.c
	$(CC) $(CFLAGS) -shared -o $@ -Wl,-soname,$@ $<


.SUFFIXES: .so
