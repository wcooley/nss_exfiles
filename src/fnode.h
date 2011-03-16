/*
 * fnode.h - File "node".
 *
 * Defines a struct containing the file path, open file handle and modification
 * time.
 *
 * Written by Wil Cooley <wcooley@nakedape.cc>
 * Copyright (C) 2011 Naked Ape Consulting, Ltd.
 *
 * Redistribution permitted under terms of the GNU GPL v2.
 */

#ifndef FNODE_H
#define FNODE_H

#include <stdio.h>
#include <sys/types.h>

struct fnode {
    char *path;         /* File path */
    FILE *handle;       /* File handle */
    time_t mtime;       /* Mod time */
};

struct fnode *fnode_new(void);
void fnode_destroy(struct fnode *);
struct fnode *fnode_set_path(struct fnode *, const char *);
FILE *fnode_fopen(struct fnode *);

#define close_handle(node)          \
    if (NULL != (node)->handle) {   \
        fclose((node)->handle);     \
        (node)->handle = NULL;      \
    }

#define is_valid_handle(handle)     \
    (((handle) != NULL) && (-1 != fileno(handle)))

#endif /* FNODE_H */
