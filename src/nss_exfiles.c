#include <limits.h>
#include <string.h>
#include <stdio.h>

#include "nss_exfiles.h"
#include "exfiles-util.h"
#include "strsplit.h"

EXFILE_FILE(passwd)

static FILE *ex_passwd_f;

/*
 * Open the passwd file for reading
 */
enum nss_status 
_nss_exfiles_setpwent(void) {

    exfiles_trace_msg("Entering _nss_exfiles_setpwent");
    return exfiles_open_file(ex_passwd, &ex_passwd_f);

}

/*
 * Close the passwd file
 */
enum nss_status 
_nss_exfiles_endpwent(void) {

    enum nss_status status = NSS_STATUS_SUCCESS;

    if (NULL != ex_passwd_f) {
        fclose(ex_passwd_f);
        ex_passwd_f = NULL;
    }

    return status;
}


enum nss_status 
_nss_exfiles_getpwent_r(struct passwd *pwbuf, 
                        char *buffer, 
                        size_t buflen, 
                        int *errnop)
{
    char **pw_entry = NULL;     /* array of strings for each passwd field */
    char pwline[MAX_CANON];     /* buffer for line from password file */
    int llength = 0;            /* actual string length of pwline */
    int scan_len;               /* FIXME Not used?  Remove */

    exfiles_trace_msg("Entering _nss_exfiles_getpwent_r");

    if (NULL == pwbuf) {
        fprintf(stderr, "pwbuf is NULL\n");
        return NSS_STATUS_NOTFOUND;
    }

    if (NULL == ex_passwd_f) {
        fprintf(stderr, "ex_passwd_f is NULL\n");
        return NSS_STATUS_NOTFOUND;
    }

    /* Read a line from the passwd file */
    if (NULL == fgets(pwline, MAX_CANON, ex_passwd_f)) {
        return NSS_STATUS_NOTFOUND;
    }
    
    llength = strlen(pwline);

    pwline[llength-1] = '\0';   /* Ensure termination */

    exfiles_trace_msg("Splitting pwline");
    pw_entry = strsplit(pwline, ':');

    if (NULL == pw_entry)
        return NSS_STATUS_NOTFOUND;

    exfiles_trace_msg("Allocating memory for passwd entry");

    if ( 0 != exfiles_alloc_passwd_from_pw_entry(pwbuf, pw_entry) ) {
        /* pwbuf is not free()d since it's passed in by the user */
        perror("Error allocating memory for member of struct passwd");
        exfiles_passwd_destroy(pwbuf);
        return NSS_STATUS_NOTFOUND;
    }

    exfiles_trace_msg("Copying pw_entry to pwbuf");

    if ( 0 != exfiles_copy_passwd_from_pw_entry(pwbuf, pw_entry) ) {
        perror("Failure copying from pw_entry to pwbuf");
        exfiles_passwd_destroy(pwbuf);
        return NSS_STATUS_NOTFOUND;
    }

    exfiles_trace_msg("Returning from _nss_exfiles_getpwent_r");

    return NSS_STATUS_SUCCESS;
}

enum nss_status 
_nss_exfiles_getpwuid_r( uid_t uid,
                         struct passwd *pwbuf,
                         char *buffer,
                         size_t buflen, 
                         int *errnop)
{
    /* Default status */
    enum nss_status status = NSS_STATUS_NOTFOUND;

    exfiles_trace_msg("Entering _nss_exfiles_getpwuid_r");

    if (NSS_STATUS_SUCCESS == _nss_exfiles_setpwent()) {
        while (NSS_STATUS_SUCCESS 
                == _nss_exfiles_getpwent_r(pwbuf, buffer, buflen, errnop)){

            if (uid == pwbuf->pw_uid) {
                status = NSS_STATUS_SUCCESS;
                break;
            }
        }
    }
    _nss_exfiles_endpwent();
    return status;
}

/* Is this actually used? */
enum nss_status 
_nss_exfiles_getpwbyuid_r(
                        uid_t uid,
                        struct passwd *pwbuf,
                        char *buffer,
                        size_t buflen, 
                        int *errnop)
{

    exfiles_trace_msg("Entering _nss_exfiles_getpwbyuid_r");

    return _nss_exfiles_getpwuid_r(
                        uid,
                        pwbuf,
                        buffer,
                        buflen, 
                        errnop
                        )
        ;

}


enum nss_status
_nss_exfiles_getpwnam_r(const char *pwnam,
                        struct passwd *pwbuf, 
                        char *buffer, 
                        size_t buflen, 
                        int *errnop)
{
    /* Default status */
    enum nss_status status = NSS_STATUS_NOTFOUND;
    int pwnam_length;

    pwnam_length = strlen(pwnam);

    if (NSS_STATUS_SUCCESS == _nss_exfiles_setpwent()) {
        while (NSS_STATUS_SUCCESS == 
                _nss_exfiles_getpwent_r(pwbuf, buffer, buflen, errnop)){
            /* Compare requested username with current entry 
             * first checking that they're the same length 
             */ 
            if (strlen(pwbuf->pw_name) != pwnam_length)
                break;

            /* then comparing by char */
            if (0 == strncmp(pwnam, pwbuf->pw_name, pwnam_length)) {
                status = NSS_STATUS_SUCCESS;
                break;
            }
        }
    }
    _nss_exfiles_endpwent();
    return status;
}

