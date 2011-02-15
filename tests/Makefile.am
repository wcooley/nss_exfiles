noinst_PROGRAMS 	= test_strlist 				\
			  test_strsplit 			\
			  test_exfiles_grp			\
			  test_exfiles_pwd			\
			  test_exfiles_util_pwd			\
			  test_exfiles_util_open		\
			  test_parser

LDADD			= @CHECK_LIBS@ -ldl
AM_CPPFLAGS		= @CHECK_CFLAGS@ -I$(top_srcdir)/src

test_strlist_SOURCES 	= test_strlist.c

test_strlist_LDADD 	= @CHECK_LIBS@ ../src/libstrlist.la

test_strsplit_SOURCES	= test_strsplit.c 			\
			  ../src/strsplit.c 			\
			  ../src/strsplit.h

test_exfiles_pwd_SOURCES = test_exfiles_pwd.c			\
			   ../src/exfiles-util-pwd.c		\
			   ../src/exfiles-util-pwd.h

test_exfiles_grp_SOURCES = test_exfiles_grp.c			\
			   ../src/strsplit.c			\
			   ../src/strsplit.h			\
			   ../src/exfiles-util-grp.c		\
			   ../src/exfiles-util-grp.h

test_exfiles_util_pwd_SOURCES = test_exfiles_util_pwd.c		\
			   ../src/exfiles-util-pwd.c		\
			   ../src/exfiles-util-pwd.h

test_exfiles_util_open_SOURCES = test_exfiles_util_open.c 	\
			   ../src/exfiles-util.c		\
			   ../src/exfiles-util.h

test_parser_SOURCES 	= test_parser.c

test_parser_LDADD = @CHECK_LIBS@ ../src/libexfiles-conf-parser.la

TESTS 			= test_strlist 				\
			  test_strsplit 			\
			  test_exfiles_grp			\
			  test_exfiles_pwd			\
			  test_exfiles_util_pwd			\
			  test_exfiles_util_open		\
			  test_parser
