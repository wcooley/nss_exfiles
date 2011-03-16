
#include <stdio.h>

#include "exfiles-conf-parser.h"

int
main (void) {

    struct exfiles_conf conf = {
        .conf_file = {
            .path = "/dev/stdin",
            .handle = stdin,
            .mtime = 0,
        },
        .passwd = NULL,
        .group = NULL,
    };

    exfiles_init_config(&conf);
    exfiles_parse_config(&conf);
    exfiles_print_config(&conf);

    return 0;
}
