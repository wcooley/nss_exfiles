#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "fnodelist.h"
#include "exfiles-util.h"
#include "exfiles-conf-parser.h"

int
exfiles_parse_config(struct exfiles_conf *conf) {

    char file[PATH_MAX+1], *qpath = NULL;
    FILE *cfgfile = conf->conf_file.handle;

    memset(file, 0, (size_t)(PATH_MAX+1));

    while (!feof(cfgfile)) {

        file[0] = '\0';

        if (fscanf(cfgfile, "# %*[^\n]\n") > 0) /* Comment */
            continue;

        if (fscanf(cfgfile, " passwd: %" XSTR(PATH_MAX) "s", file) == 1) {
            /*printf("type = passwd, file = %s\n", file);*/
            qualify_file_path(file, &qpath);
            /*fprintf(stderr, "file: %s -> qpath: %s\n", file, qpath);*/
            fnodelist_append_path(conf->passwd, qpath);
        }

        else if (fscanf(cfgfile, " group: %" XSTR(PATH_MAX) "s", file) == 1) {
            /*printf("type = group, file = %s\n", file);*/
            qualify_file_path(file, &qpath);
            /*fprintf(stderr, "file: %s -> qpath: %s\n", file, qpath);*/
            fnodelist_append_path(conf->group, qpath);
        }

        else {
            /* Gobble remaining unrecognized junk */
            fscanf(cfgfile, "%*s");
        }
    }

    /*exfiles_print_config(conf);*/

    return 0;
}

int
exfiles_init_config(struct exfiles_conf *conf) {

    /* Create a new fnodelist for passwd, if necessary */
    if (conf->passwd == NULL) {
        conf->passwd = fnodelist_new_list();
        if (conf->passwd == NULL)
            goto error_passwd;
    }

    /* Create a new fnodelist for group, if necessary */
    if (conf->group == NULL) {
        conf->group = fnodelist_new_list();
        if (conf->group == NULL)
            goto error_group;
    }

    /* Open the conf file, if necessary */
    if (conf->conf_file.handle == NULL
            && conf->conf_file.path != NULL) {
        conf->conf_file.handle = fnode_fopen(&(conf->conf_file));
        if (conf->conf_file.handle == NULL)
            goto error_conf_file;
    }

    return 0;

error_conf_file:
    fnodelist_destroy_list(conf->group);
error_group:
    fnodelist_destroy_list(conf->passwd);
error_passwd:
    return -1;
}

void
exfiles_print_config(struct exfiles_conf *conf) {
    struct fnodelist_item *listnext;

    if (NULL == conf) return;
    
    if (NULL != conf->passwd && NULL != conf->passwd->head) {
        listnext = conf->passwd->head;

        printf("passwd:");
        while (listnext != NULL && listnext->node != NULL) {
            printf(" '%s'", listnext->node->path);
            listnext = listnext->next;
        }
        printf("\n");
    }

    if (NULL != conf->group && NULL != conf->group->head) {
        listnext = conf->group->head;

        printf("group:");
        while (listnext != NULL && listnext->node != NULL) {
            printf(" '%s'", listnext->node->path);
            listnext = listnext->next;
        }
        printf("\n");
    }

}


