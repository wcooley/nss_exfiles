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
#include "exfiles-util.h"
#include "fnodelist.h"

/**
 * fnodelist_new_list - Create a new list.
 * @return Pointer to fnodelist
 */
struct fnodelist *fnodelist_new_list(void) {
    struct fnodelist *list;

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

    n = calloc(1, sizeof(struct fnodelist_item));
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
 * fnodelist_destroy_item - Destroys an fnodelist_item.
 * @param item fnodelist_item to be destroyed
 */
void fnodelist_destroy_item(struct fnodelist_item *item) {
    if (NULL != item)
        fnode_destroy(item->node);
}

/**
 * fnodelist_append_item - Appends an item to the end of a list.
 *
 * @param list List to append to.
 * @param new_item New item to be appended. If NULL, will create a new item.
 *
 * @return NULL if the list is NULL or other error; otherwise,
 * a pointer to the appended item.
 *
 */
struct fnodelist_item *fnodelist_append_item(struct fnodelist *list,
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

struct fnodelist_item *fnodelist_append_fnode(
            struct fnodelist *list, struct fnode *node) {
    struct fnodelist_item *new_item = NULL;

    if (NULL == list) return NULL;

    new_item = fnodelist_append_item(list, NULL);

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

    return new_item;
}

/**
 * fnodelist_append_path - Append an fnode with path to fnodelist.
 *
 * @param list List to append to.
 * @param path Path string in new fnode.
 *
 * @return Pointer to appended fnode or NULL on error.
 */

struct fnodelist_item *fnodelist_append_path(struct fnodelist *list, const char *path) {

    struct fnodelist_item *new_item = NULL;

    new_item = fnodelist_append_fnode(list, NULL);
    if (NULL == new_item || NULL == new_item->node) return NULL;

    fnode_set_path(new_item->node, path);

    return new_item;

}

/** fnodelist_next_item - Open next item
 *
 * @param list fnodelist to operate on
 *
 * @return Pointer to current item or NULL at EOF
 */

struct fnodelist_item *
fnodelist_next_item(struct fnodelist *list) {

    exfiles_trace_msg("Entering fnodelist_next_item");

    if (NULL == list)
        return NULL;

    if (NULL == list->curr)
        list->curr = list->head;
    else
        list->curr = list->curr->next;

    return list->curr;
}

/** fnodelist_next_fnode - Open next fnode
 *
 * @param list fnodelist to operate on
 *
 * @return Pointer to current fnode
 */

struct fnode *
fnodelist_next_fnode(struct fnodelist *list) {
    struct fnodelist_item *next;

    exfiles_trace_msg("Entering fnodelist_next_fnode");

    if (NULL == list)
        return NULL;

    next = fnodelist_next_item(list);

    if (NULL != next && NULL != fnode_fopen(next->node))
        return next->node;
    else
        return NULL;
}

/**
 * fnodelist_fgets - Read a line from an fnodelist
 *
 * @param buf Pointer to buffer to write line into.
 * @param size Maximum bytes to write to buffer.
 * @param list Fnodelist to read from.
 *
 * @return buf on success and NULL on error or EOF when no characters have been
 * read.
 */

char *
fnodelist_fgets(char *buf, int size, struct fnodelist *list) {

    char *tbuf = NULL;

    exfiles_trace_msg("Entering fnodelist_fgets");

    if (NULL == list) return NULL;

    if (NULL == list->curr)
        fnodelist_next_fnode(list);

    if (NULL == list->curr->node)
        return NULL; /* This shouldn't happen (or would it on the last node?) */

    /* Valid current handle? */
    if (is_valid_handle(list->curr->node->handle)) {
        /* At end of file? */
        if(1 == feof(list->curr->node->handle)) {
            /* Jump to next file */
            fnodelist_next_fnode(list);
        }
    }
    else {
        fnode_fopen(list->curr->node);
    }

    tbuf = fgets(buf, size, list->curr->node->handle);

    return tbuf;
}

/** fnodelist_rewind - Rewind input vector
 *
 * @param list fnodelist to operate on
 *
 * @return void
 */

void
fnodelist_rewind(struct fnodelist *list) {
    if (NULL == list)
        return;

    list->curr = list->head;

}

