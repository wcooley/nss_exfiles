#include <limits.h>
#include <string.h>
#include <stdio.h>

#include "exfiles-util.h"
#include "strsplit.h"
#include "nss_exfiles.h"

EXFILE_FILE(passwd)

static FILE *ex_passwd_f;

/*
 * Open the passwd file for reading
 */
enum nss_status 
_nss_exfiles_setpwent(void) 
{

    enum nss_status status = NSS_STATUS_SUCCESS;
    char err_msg[128] = "_nss_exfiles_setpwent: Failed to open the"
                        " password file '%s'";

    /*fprintf(stderr, "setpwent called\n");*/
    ex_passwd_f = fopen(ex_passwd, "r");

    if (NULL == ex_passwd_f) {
        sprintf(err_msg, ex_passwd);
        perror(err_msg);
        status = NSS_STATUS_UNAVAIL;
    }

    return status;
}

/*
 * Close the passwd file
 */
enum nss_status 
_nss_exfiles_endpwent(void) {

    enum nss_status status = NSS_STATUS_SUCCESS;

    if (NULL != ex_passwd_f)
        fclose(ex_passwd_f);

    return status;
}


enum nss_status 
_nss_exfiles_getpwent_r(struct passwd *pwbuf, 
                        char *buffer, 
                        size_t buflen, 
                        int *errnop)
{
    enum nss_status status = NSS_STATUS_SUCCESS;
    char **pw_entry = NULL;
    char pwline[MAX_CANON];
    int llength = 0;
    int scan_len;

    if (NULL == pwbuf) {
        fprintf(stderr, "pwbuf is NULL\n");
        return NSS_STATUS_NOTFOUND;
    }

    if (NULL == fgets(pwline, MAX_CANON, ex_passwd_f)) {
        return NSS_STATUS_NOTFOUND;
    }
    
    llength = strlen(pwline);

    pwline[llength-1] = '\0';

    pw_entry = strsplit(pwline, ':');

    if (NULL == pw_entry)
        return NSS_STATUS_NOTFOUND;

    exfiles_alloc_passwd_from_pw_entry(pwbuf, pw_entry);

    if (   NULL == pwbuf->pw_name
        || NULL == pwbuf->pw_passwd
        || NULL == pwbuf->pw_gecos
        || NULL == pwbuf->pw_dir
        || NULL == pwbuf->pw_shell
    ) {
        /* pwbuf is not free()d since it's passed in by the user */
        exfiles_passwd_destroy(pwbuf);
        perror("Error allocating memory for member of struct passwd");
        return NSS_STATUS_NOTFOUND;
    }

    if (NULL == exfiles_copy_passwd_from_pw_entry(pwbuf, pw_entry)) {
        exfiles_passwd_destroy(pwbuf);
        perror("Failure copying from pw_entry to pwbuf");
        return NSS_STATUS_NOTFOUND;
    }

    return status;
}

enum nss_status 
_nss_exfiles_getpwuid_r(uid_t uid,
                        struct passwd *pwbuf,
                        char *buffer,
                        size_t buflen, 
                        int *errnop)
{
    /* Default status */
    enum nss_status status = NSS_STATUS_NOTFOUND;

    /* fprintf(stderr, "_nss_exfiles_getpwuid_r called\n"); */

    _nss_exfiles_setpwent(); 
    while (NSS_STATUS_SUCCESS 
            == _nss_exfiles_getpwent_r(pwbuf, NULL, 0, NULL)){

        if (uid == pwbuf->pw_uid) {
            status = NSS_STATUS_SUCCESS;
            break;
        }
    }
    _nss_exfiles_endpwent();
    return status;
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

    _nss_exfiles_setpwent();
    while (NSS_STATUS_SUCCESS == _nss_exfiles_getpwent_r(pwbuf, NULL, 0, NULL)){
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
    _nss_exfiles_endpwent();
    return status;
}

