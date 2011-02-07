#ifndef NSS_EXFILES_H
#define NSS_EXFILES_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */


/* #ifndef EXFILES_BASE */
#ifdef DEV_MODE
#ifndef EXFILES_BASE
#define EXFILES_BASE "/net/rheingold/home/wcooley/nakedape/pub/small-projects/nss_exfiles/test-data/"
#endif
#else
#define EXFILES_BASE "/var/lib/exfiles"
#endif /* EXFILES_BASE */

#define EXFILE_FILE(file) static char *ex_ ## file =  EXFILES_BASE "/" #file;


#endif /* NSS_EXFILES_H */
