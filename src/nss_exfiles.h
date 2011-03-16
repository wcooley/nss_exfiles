#ifndef NSS_EXFILES_H
#define NSS_EXFILES_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */


#ifndef EXFILES_BASE
#define EXFILES_BASE "/var/lib/exfiles/"
#endif /* EXFILES_BASE */

#ifndef EXFILES_CONF
#define EXFILES_CONF "/etc/exfiles.conf"
#endif /* EXFILES_CONF */

#define EXFILE_FILE(file) static char *ex_ ## file =  EXFILES_BASE "/" #file;

#include "exfiles-conf-parser.h"

extern struct exfiles_conf nss_exfiles_conf;

int nss_exfiles_setup(void);

#endif /* NSS_EXFILES_H */
