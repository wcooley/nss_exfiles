/*
 * fnode_list.h - Linked list of file nodes.
 *
 * Written by Wil Cooley <wcooley@nakedape.cc>
 * Copyright (C) 2011 Naked Ape Consulting, Ltd.
 *
 * Redistribution permitted under terms of the GNU GPL v2.
 */

#ifndef FNODE_LIST_H
#define FNODE_LIST_H

#include "fnode.h"

struct fnode_list {
    struct fnode_list_item *head;
}

struct fnode_list_item {
    struct fnode *node;
    struct fnode_list_item *next;
}

fnode_list *fnode_list_new(void);
void fnode_list_destroy(fnode_list *);

fnode *fnode_list_append(fnode_list *, fnode *);

#endif /* FNODE_LIST_H */

