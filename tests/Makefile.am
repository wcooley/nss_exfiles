bin_PROGRAMS = test_strlist test_strsplit test_exfiles_pwd

test_strlist_SOURCES 	= test_strlist.c 		\
			  ../src/strlist.c 		\
			  ../src/strlist.h
			  
test_strlist_LDADD 	= -lcheck

test_strsplit_SOURCES	= test_strsplit.c 		\
			  ../src/strsplit.c 		\
			  ../src/strsplit.h
test_strsplit_LDADD	= -lcheck

test_exfiles_pwd_SOURCES = test_exfiles_pwd.c

test_exfiles_pwd_LDADD	= -lcheck -ldl

AM_CPPFLAGS		= -I$(top_srcdir)/src

TESTS 			= test_strlist test_strsplit test_exfiles_pwd
