#include <errno.h>
#include <grp.h>
#include <limits.h>
#include <nss.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "nss_exfiles.h"
#include "exfiles-util.h"
#include "exfiles-util-grp.h"
#include "strsplit.h"

EXFILE_FILE(group)

static FILE *ex_group_f;

/*
 * Open the group file for reading
 */
enum nss_status
_nss_exfiles_setgrent(void) {

    exfiles_trace_msg("Entering _nss_exfiles_setgrent");
    return exfiles_open_file(ex_group, &ex_group_f);

}

/*
 * Close the group file
 */
enum nss_status
_nss_exfiles_endgrent(void) {

    enum nss_status status = NSS_STATUS_SUCCESS;

    if (NULL != ex_group_f) {
        fclose(ex_group_f);
        ex_group_f = NULL;
    }

    return status;

}


enum nss_status
_nss_exfiles_getgrent_r(struct group *grbuf,
                        char *buffer,
                        size_t buflen,
                        int *errnop)
{
    char **gr_entry = NULL;     /* array of strings for each group field */
    char grline[MAX_CANON];     /* buffer for line from group file */
    int llength = 0;            /* string lenght of grline */

    exfiles_trace_msg("Entering _nss_exfiles_getgrent_r");

    if (NULL == grbuf) {
        fprintf(stderr, "grbuf is NULL\n");
        return NSS_STATUS_NOTFOUND;
    }

    if (NULL == ex_group_f) {
        fprintf(stderr, "ex_group_f is NULL\n");
        return NSS_STATUS_NOTFOUND;
    }

    /* Read a line from the group file */
    if (NULL == fgets(grline, MAX_CANON, ex_group_f)) {
        return NSS_STATUS_NOTFOUND;
    }

    llength = strlen(grline);

    grline[llength-1] = '\0';   /* Ensure termination */

    exfiles_trace_msg("Splitting grline");
    gr_entry = strsplit(grline, ':');

    if (NULL == gr_entry)
        return NSS_STATUS_NOTFOUND;

    exfiles_trace_msg("Allocating memory for group entry");

    if ( 0 != exfiles_alloc_group_from_gr_entry(grbuf, gr_entry) ) {
        perror("Error allocating memory for member of struct group");
        exfiles_group_destroy(grbuf);
        return NSS_STATUS_NOTFOUND;
    }

    exfiles_trace_msg("Copying gr_entry to grbuf");

    if ( 0 != exfiles_copy_group_from_gr_entry(grbuf, gr_entry) ) {
        perror("Failure copying from gr_entry to grbuf");
        exfiles_group_destroy(grbuf);
        return NSS_STATUS_NOTFOUND;
    }

    exfiles_trace_msg("Returning from _nss_exfiles_getgrent_r");

    return NSS_STATUS_SUCCESS;
}
    

enum nss_status
_nss_exfiles_getgrgid_r(
                        gid_t gid,
                        struct group *grbuf,
                        char *buffer,
                        size_t buflen,
                        int *errnop)
{
    /* Default status */
    enum nss_status status = NSS_STATUS_NOTFOUND;

    exfiles_trace_msg("Entering _nss_exfiles_getgrgid_r");

    if (NSS_STATUS_SUCCESS == _nss_exfiles_setgrent()) {
        while (NSS_STATUS_SUCCESS
                == _nss_exfiles_getgrent_r(grbuf, buffer, buflen, errnop)) {

            if (gid == grbuf->gr_gid) {
                status = NSS_STATUS_SUCCESS;
                break;
            }
        }
    }
    _nss_exfiles_endgrent();
    return status;
}

enum nss_status
_nss_exfiles_getgrnam_r(const char *grnam,
                        struct group *grbuf,
                        char *buffer,
                        size_t buflen,
                        int *errnop)
{

    /* Default status */
    enum nss_status status = NSS_STATUS_NOTFOUND;
    int grname_length;

    grname_length = strlen(grnam);

    if (NSS_STATUS_SUCCESS == _nss_exfiles_setgrent()) {
        while (NSS_STATUS_SUCCESS == 
                _nss_exfiles_getgrent_r(grbuf, buffer, buflen, errnop)){
            /* Compare requested group name with current entry 
             * first checking that they're the same length 
             */ 
            if (strlen(grbuf->gr_name) != grname_length)
                break;

            /* then comparing by char */
            if (0 == strncmp(grnam, grbuf->gr_name, grname_length)) {
                status = NSS_STATUS_SUCCESS;
                break;
            }
        }
    }
    _nss_exfiles_endgrent();
    return status;
}
