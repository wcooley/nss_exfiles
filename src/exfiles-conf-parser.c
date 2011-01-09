#include <limits.h>
#include <stdio.h>
#include "strlist.h"

#define MAX_NSS 10 /* "protocols" and "publickey" are both strlen 9 */

#define XSTR(s) STR(s)
#define STR(s) #s

int
nss_exfiles_parse_config (FILE *cfg) {

    char type[MAX_NSS], file[PATH_MAX+1];

    while (!feof(cfg)) {

        if (fscanf(cfg, "# %*[^\n]\n") > 0) /* Comment */
            continue;

        if (fscanf(cfg, " %" XSTR(MAX_NSS)  "[a-z]:"
                        " %" XSTR(PATH_MAX) "s ",
                            type, file) == 2 ) {
            printf("type = %s, file = %s\n", type, file);
        }

        type[0] = file[0] = '\0';
    }
    return 0;
}

/*
int
nss_exfiles_init_config(k
*/

int
main (void) {
    nss_exfiles_parse_config(stdin);

    return 0;
}
