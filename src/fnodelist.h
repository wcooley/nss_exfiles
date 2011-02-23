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

typedef struct _fnodelist_node {
    struct _fnodelist_node  *next;
    char *string;
}   fnodelist_node;

typedef struct _fnodelist {
    fnodelist_node *head;
}   fnodelist;

fnodelist      *fnodelist_create_list(void);
fnodelist_node *fnodelist_create_node(void);

void fnodelist_destroy_list(fnodelist *list);
void fnodelist_destroy_node(fnodelist_node *node);

fnodelist_node *fnodelist_node_set_str(fnodelist_node *node, const char *str);
fnodelist_node *fnodelist_append_str(fnodelist *list, const char *str);
fnodelist_node *fnodelist_append_node(fnodelist *list, fnodelist_node *node);


#endif /* FNODELIST_H */
