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

#ifndef EXFILES_BASE
#define EXFILES_BASE "/var/lib/exfiles"
#endif /* EXFILES_BASE */

#define EXFILE_FILE(file) static char * ex_ ## file =  EXFILES_BASE "/" #file;



