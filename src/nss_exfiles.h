#ifndef NSS_EXFILES_H
#define NSS_EXFILES_H 1

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <errno.h>
#include <netdb.h>
#include <nss.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

/* #ifndef EXFILES_BASE */
#ifdef DEV_MODE
#define EXFILES_BASE "/net/rheingold/home/wcooley/nakedape/pub/small-projects/nss_exfiles/test-data/"
#else
#define EXFILES_BASE "/var/lib/exfiles"
#endif /* EXFILES_BASE */

#define EXFILE_FILE(file) static char * ex_ ## file =  EXFILES_BASE "/" #file;


#endif /* NSS_EXFILES_H */
