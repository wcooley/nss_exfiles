lib_LTLIBRARIES 	= libnss_exfiles.la
libnss_exfiles_la_SOURCES = conf_parser.y 		\
			    conf_lexer.l 		\
			    exfiles-util.c		\
			    exfiles-util.h		\
			    exfiles-util-grp.c		\
			    exfiles-util-grp.h		\
			    exfiles-util-pwd.c		\
			    exfiles-util-pwd.h		\
			    nss_exfiles_grp.c		\
			    nss_exfiles_pwd.c 		\
			    nss_exfiles.h 		\
			    strsplit.c 			\
			    strsplit.h 			\
			    strlist.c 			\
			    strlist.h 
libnss_exfiles_la_LDFLAGS = -version-info 2:0:0

AM_YFLAGS = -d
