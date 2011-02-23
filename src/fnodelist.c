/*
 * fnodelist.h - Linked list of file nodes.
 *
 * Written by Wil Cooley <wcooley@nakedape.cc>
 * Copyright (C) 2005 Naked Ape Consulting, Ltd.
 *
 * Redistribution permitted under terms of the GNU GPL v2.
 *
 */

#include <stdlib.h>
#include <string.h>
#include "fnodelist.h"

/**
 * fnodelist_new_list - Create a new list.
 * @return Pointer to fnodelist
 */
struct fnodelist *fnodelist_new_list(void) {
    struct fnodelist *list;
    int ret;

    list = calloc(1, sizeof(struct fnodelist));
    if (NULL == list) return NULL;

    return list;

}

/**
 * fnodelist_new_item - Create a new, empty node.
 * @return Pointer to an fnodelist_item.
 */
struct fnodelist_item *fnodelist_new_item(void) {
    struct fnodelist_item *n;

    n = malloc(sizeof(struct fnodelist_item));
    if (NULL == n) return NULL;

    return n;
}

/**
 * fnodelist_destroy_list - Destroy a list, freeing nodes and their data.
 * @param list fnodelist to be destroyed
 */
void fnodelist_destroy_list(struct fnodelist *list) {
    struct fnodelist_item *curr, *next;

    /* A list that isn't */
    if (NULL == list)
        return;

    /* List has at least one node */
    if (NULL != list->head) {
        curr = list->head;
        do {
            next = curr->next;
            fnode_destroy(curr->node);
            curr = next;
        } while (NULL != curr);
    }

    free((void *)list);

    return;

}

/**
 * fnodelist_append - Appends an item to the end of a list.
 *
 * @param list List to append to.
 * @param new_item New item to be appended. If NULL, will create a new item.
 *
 * @return NULL if the list is NULL or other error; otherwise,
 * a pointer to the appended item.
 *
 */
struct fnodelist_item *fnodelist_append(struct fnodelist *list,
                                        struct fnodelist_item *new_item) {

    struct fnodelist_item *curr = NULL;

    /* Bogus input */
    if (NULL == list)
        return NULL;

    /* Create new item since one wasn't provided */
    if (NULL == new_item) {
        new_item = fnodelist_new_item();
        if (NULL == new_item) return NULL;
    }

    /* Empty list */
    if (NULL == list->head) {
        list->head = new_item;
        list->head->next = NULL;
        return list->head;
    }

    curr = list->head;

    while (NULL != curr->next)
        curr = curr->next;

    curr->next = new_item;
    curr->next->next = NULL;
    return curr->next;
}

/**
 * fnodelist_append_fnode - Append an fnode to an fnodelist, hiding the
 * fnodelist_item from the user.
 *
 * @param list List to append fnode to.
 * @param node Pointer to fnode to append to list or create if NULL.
 *
 * @return Pointer to appended fnode or NULL on error.
 */

struct fnode *fnodelist_append_fnode(fnodelist *list, fnode *node) {
    struct fnodelist_item *new_item = NULL;

    if (NULL == list) return NULL;

    new_item = fnodelist_append(list, NULL);

    if (NULL == new_item)
        return NULL;

    if (NULL == node) {
        node = fnode_new();
        if (NULL == node) {
            free(new_item);
            return NULL;
        }
    }

    new_item->node = node;

    return new_item->node;
}

/**
 * fnodelist_append_path - Append an fnode with path to fnodelist.
 *
 * @param list List to append to.
 * @param path Path string in new fnode.
 *
 * @return Pointer to appended fnode or NULL on error.
 */

struct fnode *fnodelist_append_path(fnodelist *list, char *path) {

    struct fnode *new_node = NULL;

    new_node = fnodelist_append_fnode(list, NULL);
    if (NULL == new_node) return NULL;

    return fnode_set_path(new_node, path);

}
