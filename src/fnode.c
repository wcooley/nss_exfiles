
/*
 * fnode_new - Create a new, empty node.  Returns a pointer to a
 * fnode.
 */
fnode *fnode_new(void) {
    fnode *n;

    n = malloc(sizeof(fnode));
    if (NULL == n) return NULL;

    if (NULL == memset(n, 0, sizeof(fnode))) {
        free(n);
        return NULL;
    }

    return n;
}

/*
 * fnode_destroy - Destroy an fnode, taking care to clean-up if necessary.
 */
void fnode_destroy(fnode *node) {

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

