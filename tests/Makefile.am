bin_PROGRAMS 		= test_strlist 			\
			  test_strsplit 		\
			  test_exfiles_pwd		\
			  test_exfiles_util		

test_strlist_SOURCES 	= test_strlist.c 		\
			  ../src/strlist.c 		\
			  ../src/strlist.h
			  
test_strlist_LDADD 	= -lcheck

test_strsplit_SOURCES	= test_strsplit.c 		\
			  ../src/strsplit.c 		\
			  ../src/strsplit.h

test_strsplit_LDADD	= -lcheck

test_exfiles_pwd_SOURCES = test_exfiles_pwd.c		\
			   ../src/exfiles-util.c	\
			   ../src/exfiles-util.h	

test_exfiles_pwd_LDADD	= -lcheck -ldl

test_exfiles_util_SOURCES = test_exfiles_util.c		\
			   ../src/exfiles-util.c	\
			   ../src/exfiles-util.h	

test_exfiles_util_LDADD	= -lcheck

AM_CPPFLAGS		= -I$(top_srcdir)/src

TESTS 			= test_strlist 			\
			  test_strsplit 		\
			  test_exfiles_pwd		\
			  test_exfiles_util
