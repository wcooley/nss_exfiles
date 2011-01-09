/*
 * string_list.h - Basic linked-list-of-strings implementation.
 *
 * Written by Wil Cooley <wcooley@nakedape.cc>
 * Copyright (C) 2005 Naked Ape Consulting, Ltd.
 *
 * Redistribution permitted under terms of the GNU GPL v2.
 *
 */

#ifndef STRLIST_H
#define STRLIST_H

#include <semaphore.h>

typedef struct _strlist_node {
    struct _strlist_node  *next;
    char *string;
}   strlist_node;

typedef struct _strlist {
    strlist_node *head;
    sem_t lock;
}   strlist;

strlist      *strlist_create_list(void);
strlist_node *strlist_create_node(void);

void strlist_destroy_list(strlist *list);
void strlist_destroy_node(strlist_node *node);

strlist_node *strlist_node_set_str(strlist_node *node, const char *str);
strlist_node *strlist_append_str(strlist *list, const char *str);
strlist_node *strlist_append_node(strlist *list, strlist_node *node);


#endif /* STRLIST_H */
