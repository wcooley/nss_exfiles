#include <stdio.h>
#include "strlist.h"

int
nss_exfiles_parse_config (FILE *cfg) {

    char type[64], file[64];

    while (!feof(cfg)) {

        if (fscanf(cfg, "# %*[^\n]\n") > 0) /* Comment */
            continue;

        if (fscanf(cfg, " %[a-z]: %s ", type, file) > 0) {
            printf("type = %s, file = %s\n", type, file);
        }

        type[0] = file[0] = '\0';
    }
    return 0;
}

int
main (void) {
    _nss_exfiles_parse_config(stdin);

    return 0;
}
