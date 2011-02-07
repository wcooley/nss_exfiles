lib_LTLIBRARIES 	= libnss_exfiles.la
noinst_LTLIBRARIES	= libstrlist.la libexfiles-conf-parser.la

libnss_exfiles_la_SOURCES = exfiles-util.c		\
			    exfiles-util.h		\
			    exfiles-util-grp.c		\
			    exfiles-util-grp.h		\
			    exfiles-util-pwd.c		\
			    exfiles-util-pwd.h		\
			    nss_exfiles_grp.c		\
			    nss_exfiles_pwd.c 		\
			    nss_exfiles.h 		\
			    strsplit.c 			\
			    strsplit.h

libnss_exfiles_la_LIBADD = libstrlist.la libexfiles-conf-parser.la

libnss_exfiles_la_LDFLAGS = -version-info 2:0:0

libstrlist_la_SOURCES = strlist.c strlist.h

libexfiles_conf_parser_la_SOURCES = exfiles-conf-parser.c \
				    exfiles-conf-parser.h

libexfiles_conf_parser_la_LIBADD = libstrlist.la

AM_YFLAGS = -d --name-prefix=_nss_exfiles_
AM_LFLAGS = -P_nss_exfiles_
