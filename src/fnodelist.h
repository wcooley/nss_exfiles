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
    struct fnodelist_item *head;
};

struct fnodelist      *fnodelist_new_list(void);
struct fnodelist_item *fnodelist_new_item(void);

void fnodelist_destroy_list(struct fnodelist *);
void fnodelist_destroy_item(struct fnodelist_item *);


struct fnodelist_item *fnodelist_append_item(struct fnodelist *,
                                             struct fnodelist_item *);
struct fnodelist_item *fnodelist_append_fnode(struct fnodelist *, struct fnode *);
struct fnodelist_item *fnodelist_append_path(struct fnodelist *, const char *);


#endif /* FNODELIST_H */
