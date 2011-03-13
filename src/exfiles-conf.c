
#include <stdio.h>

#include "exfiles-conf-parser.h"

int
main (void) {

    struct exfiles_conf conf;

    exfiles_init_config(&conf);
    exfiles_parse_config(stdin, &conf);
    exfiles_print_config(&conf);

    return 0;
}
