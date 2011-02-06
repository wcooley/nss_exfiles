/*
 * strlist.h - Basic linked-list-of-strings implementation.
 *
 * Written by Wil Cooley <wcooley@nakedape.cc>
 * Copyright (C) 2005 Naked Ape Consulting, Ltd.
 *
 * Redistribution permitted under terms of the GNU GPL v2.
 *
 */

#include <stdlib.h>
#include <string.h>
#include "strlist.h"

/*
 * strlist_create_list - Create a new list.  Returns a pointer to strlist.
 */
strlist *strlist_create_list(void) {
    strlist *list;
    int ret;

    list = calloc(1, sizeof(strlist));
    if (NULL == list) return NULL;

    return list;

}

/*
 * strlist_create_node - Create a new, empty node.  Returns a pointer to a
 * strlist_node.
 */
strlist_node *strlist_create_node(void) {
    strlist_node *n;

    n = malloc(sizeof(strlist_node));
    if (NULL == n) return NULL;

    n->next = NULL;
    n->string = NULL;

    return n;
}

/*
 * strlist_destroy_list - Destroy a list, freeing nodes and their data.
 */
void strlist_destroy_list(strlist *list) {
    strlist_node *curr, *next;

    /* A list that isn't */
    if (NULL == list)
        return;

    /* List has at least one node */
    if (NULL != list->head) {
        curr = list->head;
        do {
            next = curr->next;
            strlist_destroy_node(curr);
            curr = next;
        } while (NULL != curr);
    }

    free((void *)list);

    return;

}

/*
 * strlist_destroy_node - Destroy a node, including data.
 */
void strlist_destroy_node(strlist_node *node) {

    /* A node that isn't */
    if (NULL == node)
        return;

    if (NULL != node->string)
        free((void*)node->string);

    free((void*)node);
}

/*
 * strlist_append_node - Appends a node to the end of a list.  Returns NULL if
 * the passed new_node or list is NULL; otherwise, returns a pointer to the
 * appended node.
 */
strlist_node *strlist_append_node(strlist *list, strlist_node *new_node) {
    strlist_node *curr = NULL;

    /* Bogus input */
    if ((NULL == new_node) || (NULL == list))
        return NULL;

    /* Empty list */
    if (NULL == list->head) {
        list->head = new_node;
        list->head->next = NULL;
        return list->head;
    }

    curr = list->head;

    while (NULL != curr->next)
        curr = curr->next;

    curr->next = new_node;
    curr->next->next = NULL;
    return curr->next;
}

/*
 * strlist_node_set_str - Given a node and a string, copy the string into the
 * node, first freeing any existing string.  As a special case, if str is
 * NULL, just free the existing string.  Returns the node pointer or NULL on
 * error.
 */

strlist_node *strlist_node_set_str(strlist_node *node, const char *str) {

    int lenstr = 0;

    if (NULL == node)
        return NULL;

    if (NULL != node->string) {
        free(node->string);
        node->string = NULL;
    }

    if (NULL == str)
        return node;

    lenstr = strlen(str) + 1;
    node->string = malloc(sizeof(char) *lenstr);

    if (NULL == node->string)
        return NULL;

    strncpy(node->string, str, lenstr);

    return node;
}

/*
 * strlist_append_str - Given a list and string, create and append a new node
 * with the string.  Returns NULL on error and a pointer to the new node on
 * success.
 */

strlist_node *strlist_append_str(strlist *list, const char *str) {
    strlist_node *tmpnode = NULL;
    int lenstr = 0;

    tmpnode = strlist_create_node();

    if (NULL == tmpnode)
        return NULL;

    tmpnode = strlist_node_set_str(tmpnode, str);

    if (NULL == tmpnode)
        return NULL;

    return strlist_append_node(list, tmpnode);
}
