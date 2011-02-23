/*
 * fnodelist.h - Linked list of fnodes.
 *
 * Written by Wil Cooley <wcooley@nakedape.cc>
 * Copyright (C) 2005 Naked Ape Consulting, Ltd.
 *
 * Redistribution permitted under terms of the GNU GPL v2.
 *
 */

#ifndef FNODELIST_H
#define FNODELIST_H

#include "fnode.h"

struct fnodelist_item {
    struct fnodelist_item  *next;
    struct fnode *node;
};

struct fnodelist {
    fnodelist_item *head;
};

fnodelist      *fnodelist_new_list(void);
fnodelist_item *fnodelist_new_item(void);

void fnodelist_destroy_list(fnodelist *);

struct fnodelist_item *fnodelist_append(fnodelist *, fnodelist_item *);
struct fnode *fnodelist_append_fnode(fnodelist *, fnode *);
struct fnode *fnodelist_append_path(fnodelist *, char *);


#endif /* FNODELIST_H */
