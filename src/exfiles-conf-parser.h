#ifndef EXFILES_CONF_PARSER_H
#define EXFILES_CONF_PARSER_H

#include "strlist.h"

struct exfiles_conf {
    strlist *passwd;
    strlist *group;
};

int exfiles_parse_config(FILE *cfgfile, struct exfiles_conf *c);

int exfiles_init_config(struct exfiles_conf *c);

void exfiles_print_config(struct exfiles_conf *c);

#endif /* EXFILES_CONF_PARSER_H */
