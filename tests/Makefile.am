noinst_PROGRAMS 	= test_strlist 				\
			  test_strsplit 			\
			  test_exfiles_grp			\
			  test_exfiles_pwd			\
			  test_exfiles_util_pwd			\
			  test_exfiles_util_open		\
			  test_parser

test_strlist_SOURCES 	= test_strlist.c

test_strlist_LDADD 	= -lcheck ../src/libstrlist.la


test_strsplit_SOURCES	= test_strsplit.c 			\
			  ../src/strsplit.c 			\
			  ../src/strsplit.h

test_strsplit_LDADD	= -lcheck


test_exfiles_pwd_SOURCES = test_exfiles_pwd.c			\
			   ../src/exfiles-util-pwd.c		\
			   ../src/exfiles-util-pwd.h

test_exfiles_pwd_LDADD	= -lcheck -ldl


test_exfiles_grp_SOURCES = test_exfiles_grp.c			\
			   ../src/strsplit.c			\
			   ../src/strsplit.h			\
			   ../src/exfiles-util-grp.c		\
			   ../src/exfiles-util-grp.h

test_exfiles_grp_LDADD	= -lcheck -ldl



test_exfiles_util_pwd_SOURCES = test_exfiles_util_pwd.c		\
			   ../src/exfiles-util-pwd.c		\
			   ../src/exfiles-util-pwd.h

test_exfiles_util_pwd_LDADD = -lcheck


test_exfiles_util_open_SOURCES = test_exfiles_util_open.c 	\
			   ../src/exfiles-util.c		\
			   ../src/exfiles-util.h

test_exfiles_util_open_LDADD = -lcheck

test_parser_SOURCES 	= test_parser.c

test_parser_LDADD = ../src/libexfiles-conf-parser.la -lcheck

AM_CPPFLAGS		= -I$(top_srcdir)/src

TESTS 			= test_strlist 				\
			  test_strsplit 			\
			  test_exfiles_grp			\
			  test_exfiles_pwd			\
			  test_exfiles_util_pwd			\
			  test_exfiles_util_open		\
			  test_parser
