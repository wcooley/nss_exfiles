
#include <nss.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strsplit.h"

/*************************************************************************
 * group functions
 *************************************************************************/

/*
 * Allocate memory for items in struct group base on string array from
 * strsplit
 */
int
exfiles_alloc_group_from_gr_entry(struct group *grbuf, char **gr_entry) {

    grbuf->gr_name      = malloc(sizeof(char) *(strlen(gr_entry[0])+1));
    grbuf->gr_passwd    = malloc(sizeof(char) *(strlen(gr_entry[1])+1));

    if (    grbuf->gr_name      == NULL
        ||  grbuf->gr_passwd    == NULL
    )
        return -1;

    return 0;
}

/*
 * Fill in struct group from gr_entry
 */
int
exfiles_copy_group_from_gr_entry(struct group *grbuf, char **gr_entry)
{
    int tmplen = 0;

    tmplen = strlen(gr_entry[0]);
    strncpy(grbuf->gr_name, gr_entry[0], tmplen+1);

    if (strlen(grbuf->gr_name) != tmplen)
        return -1;

    tmplen = strlen(gr_entry[1]);
    strncpy(grbuf->gr_passwd, gr_entry[1], tmplen+1);

    if (strlen(grbuf->gr_passwd) != tmplen)
        return -1;

    grbuf->gr_gid = (gid_t)atoi(gr_entry[2]);

    /* Split the members by comma */
    grbuf->gr_mem = strsplit(gr_entry[3], ',');

    fprintf(stderr, "group feature not complete in %s:%d\n", __FILE__, __LINE__);
    abort();
    return 0;
}

/*
 * struct group destructor
 */
void
exfiles_group_destroy(struct group *grbuf)
{
    if ( NULL != grbuf ) {
        if ( NULL != grbuf->gr_name ) {
            free(grbuf->gr_name);
            grbuf->gr_name = NULL;
        }

        if ( NULL != grbuf->gr_passwd ) {
            free(grbuf->gr_passwd);
            grbuf->gr_passwd = NULL;
        }

        grbuf->gr_gid = (gid_t) -1;

        if ( NULL != grbuf->gr_mem ) {
            strsplit_free(grbuf->gr_mem);
            grbuf->gr_mem = NULL;
        }
    }
}
