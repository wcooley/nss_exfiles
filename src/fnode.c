
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "config.h"
#include "exfiles-util.h"
#include "fnode.h"

/*
 * fnode_new - Create a new, empty node.  Returns a pointer to a
 * fnode.
 */
struct fnode *fnode_new(void) {
    struct fnode *n;

    n = calloc(1, sizeof(struct fnode));
    if (NULL == n) return NULL;

    return n;
}

/*
 * fnode_destroy - Destroy an fnode, taking care to clean-up if necessary.
 */
void fnode_destroy(struct fnode *node) {

    /* A node that isn't */
    if (NULL == node)
        return;

    if (NULL != node->path)
        free(node->path);

    if (NULL != node->handle) {
        if (0 == fclose(node->handle)) {
            node->handle = NULL;
        }
        else {
            /* FIXME: Figure out what to do if fclose returns an error */
        }
    }

    free(node);
}

/**
 * fnode_set_path - Copy path into fnode, freeing any existing path. As a
 * special case, if path is NULL, then just free existing string.
 *
 * @param node Node to copy path to.
 * @param path Path string to copy to node.
 *
 * @return Pointer to node or NULL on error.
 */

struct fnode *fnode_set_path(struct fnode *node, const char *path) {

    int lenstr = 0;

    if (strlen(path) > PATH_MAX)
        return NULL;

    if (NULL == node)
        return NULL;

    if (NULL != node->path) {
        free(node->path);
        node->path = NULL;

        /* Also close the filehandle if it's open--otherwise it would get
           lost */
        close_handle(node);
    }

    if (NULL == path)
        return node;

    lenstr = strlen(path) + 1;
    node->path = calloc(1, sizeof(char)*lenstr);

    if (NULL == node->path)
        return NULL;

    strncpy(node->path, path, lenstr);

    return node;
}

/**
 * fnode_fopen - Open file path if necessary. It is "necessary" if it is not
 * already open and the existing file's mtime is later than the fnode's
 * mtime.
 *
 * @param node fnode with path to open.
 *
 * @return Pointer to FILE or NULL on error.
 *
 * FIXME Should we be paranoid about ownership & permissions? Should we track
 * & compare inode too?
 */

FILE *fnode_fopen(struct fnode *node) {

    struct stat *pathstat;

    if (NULL == node->path) return NULL;

    if (NULL != node->handle) {     /* handle is already open */
        if (stat(node->path, pathstat) != 0)
            return NULL;

        /* If open file has as late mtime as path, then just rewind the
         * handle and return it */
        if (pathstat->st_mtime <= node->mtime) {
            rewind(node->handle);
            return node->handle;
        }

        /* Otherwise, start over */
        close_handle(node);
    }

    exfiles_open_file(node->path, &(node->handle));

    exfiles_set_close_on_exec(node->handle);

    return node->handle;
}
