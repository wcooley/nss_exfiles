bin_PROGRAMS		= exfiles-conf

lib_LTLIBRARIES 	= libnss_exfiles.la
noinst_LTLIBRARIES	= libexfiles-conf-parser.la

libnss_exfiles_la_SOURCES = exfiles-util.c		\
			    exfiles-util.h		\
			    exfiles-util-grp.c		\
			    exfiles-util-grp.h		\
			    exfiles-util-pwd.c		\
			    exfiles-util-pwd.h		\
			    fnode.c			\
			    fnode.h			\
			    fnodelist.c			\
			    fnodelist.h			\
			    nss_exfiles_grp.c		\
			    nss_exfiles_pwd.c 		\
			    nss_exfiles.c 		\
			    nss_exfiles.h 		\
			    strsplit.c 			\
			    strsplit.h

libnss_exfiles_la_LIBADD = libexfiles-conf-parser.la

libnss_exfiles_la_LDFLAGS = -version-info 2:0:0 \
			    -export-symbols-regex '^(_nss_exfiles_|_set_passwd_file)'

libexfiles_conf_parser_la_SOURCES = exfiles-conf-parser.c \
				    exfiles-conf-parser.h

exfiles_conf_CFLAGS = $(AM_CFLAGS)

exfiles_conf_SOURCES = exfiles-conf.c			\
			fnode.c				\
			fnode.h				\
			fnodelist.c			\
			fnodelist.h			\
			exfiles-util.c			\
			exfiles-util.h			\
			exfiles-conf-parser.c		\
			exfiles-conf-parser.h

