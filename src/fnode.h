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

struct fnode {
    char *path;         /* File path */
    FILE *handle;       /* File handle */
    time_t mtime;       /* Mod time */
};

fnode *fnode_new(void);
void fnode_destroy(fnode *);

#endif /* FNODE_H */
