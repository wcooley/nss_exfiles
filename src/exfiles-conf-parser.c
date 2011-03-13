#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "fnodelist.h"
#include "exfiles-conf-parser.h"

#define XSTR(s) STR(s)
#define STR(s) #s

int
exfiles_parse_config(FILE *cfgfile, struct exfiles_conf *conf) {

    char file[PATH_MAX+1];

    while (!feof(cfgfile)) {

        file[0] = '\0';

        if (fscanf(cfgfile, "# %*[^\n]\n") > 0) /* Comment */
            continue;

        if (fscanf(cfgfile, " passwd: %" XSTR(PATH_MAX) "s", file) == 1) {
            /*printf("type = passwd, file = %s\n", file);*/
            fnodelist_append_path(conf->passwd, file);
        }

        else if (fscanf(cfgfile, " group: %" XSTR(PATH_MAX) "s", file) == 1) {
            /*printf("type = group, file = %s\n", file);*/
            fnodelist_append_path(conf->group, file);
        }

        else {
            /* Gobble remaining unrecognized junk */
            fscanf(cfgfile, "%*s");
        }
    }

    /* exfiles_print_config(conf); */

    return 0;
}

int
exfiles_init_config(struct exfiles_conf *conf) {

    conf->passwd = fnodelist_new_list();
    if (conf->passwd == NULL)
        return -1;

    conf->group = fnodelist_new_list();
    if (conf->group == NULL) {
        fnodelist_destroy_list(conf->passwd);
        return -1;
    }

    return 0;
}

void
exfiles_print_config(struct exfiles_conf *conf) {
    struct fnodelist_item *listnext;

    listnext = conf->passwd->head;

    printf("passwd:");
    while (listnext != NULL) {
        printf(" '%s'", listnext->node->path);
        listnext = listnext->next;
    }
    printf("\n");

    listnext = conf->group->head;

    printf("group:");
    while (listnext != NULL) {
        printf(" '%s'", listnext->node->path);
        listnext = listnext->next;
    }
    printf("\n");

}


