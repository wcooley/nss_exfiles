#include <nss.h>

#include "exfiles-conf-parser.h"
#include "fnode.h"
#include "nss_exfiles.h"

struct exfiles_conf nss_exfiles_conf = {
    .conf_file = {
        .path = EXFILES_CONF,
        .handle = NULL,
        .mtime = (time_t)0
    },
    .passwd = NULL,
    .group = NULL
};

int nss_exfiles_setup(void) {
    if (-1 == exfiles_init_config(&nss_exfiles_conf))
        return NSS_STATUS_TRYAGAIN;

    if (-1 == exfiles_parse_config(&nss_exfiles_conf))
        return NSS_STATUS_TRYAGAIN;

    return NSS_STATUS_SUCCESS;
}
