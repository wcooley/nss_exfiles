#ifndef EXFILES_CONF_PARSER_H
#define EXFILES_CONF_PARSER_H

#include "fnodelist.h"

struct exfiles_conf {
    struct fnode conf_file;
    struct fnodelist *passwd;
    struct fnodelist *group;
};

int exfiles_parse_config(struct exfiles_conf *c);

int exfiles_init_config(struct exfiles_conf *c);

void exfiles_print_config(struct exfiles_conf *c);

#endif /* EXFILES_CONF_PARSER_H */
