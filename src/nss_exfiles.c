#include <limits.h>
#include <string.h>
#include <stdio.h>

#include "nss_exfiles.h"
#include "strsplit.h"

EXFILE_FILE(passwd)

static FILE * ex_passwd_f;


enum nss_status _nss_exfiles_setpwent(void) {
    enum nss_status status = NSS_STATUS_SUCCESS;
/*    fprintf(stderr, "Calling %d\n", __LINE__); */

    ex_passwd_f = fopen(ex_passwd, "r");

/*    fprintf(stderr, "Opened passwd\n"); */

    if (NULL == ex_passwd_f) {
        /* FIXME Use perror */
        fprintf(stderr, "Filed to open the password file '%s'\n", ex_passwd);
        status = NSS_STATUS_UNAVAIL;
    }

    return status;
}

enum nss_status _nss_exfiles_endpwent(void) {
    enum nss_status status = NSS_STATUS_SUCCESS;
/*    fprintf(stderr, "Calling %d\n", __LINE__);*/

    if (NULL != ex_passwd_f)
        fclose(ex_passwd_f);

    return status;
}


enum nss_status _nss_exfiles_getpwent_r (struct passwd *pwbuf, 
                                        char *buffer, 
                                        size_t buflen, 
                                        int *errnop)
{
    enum nss_status status = NSS_STATUS_SUCCESS;
    char ** pw_entry = NULL;
    char pwline[MAX_CANON];
    int llength = 0;

    /*
    pwbuf = malloc(sizeof(struct passwd));

    if (NULL == pwbuf) {
        fprintf(stderr, "pwbuf is NULL\n");
        exit(1);
    }
    else
        fprintf(
    */

    /* fprintf(stderr, "Calling %d\n", __LINE__); */

    if (NULL == fgets(pwline, MAX_CANON, ex_passwd_f))
        return NSS_STATUS_NOTFOUND;
    
    llength = strlen(pwline);

    pwline[llength-1] = '\0';
/*    fprintf(stderr, "Read line '%s'\n", pwline); */

    pw_entry = strsplit(pwline, ':');

    if (NULL == pw_entry)
        return NSS_STATUS_NOTFOUND;

    /* Copy username */
    pwbuf->pw_name = malloc(sizeof(char) * (strlen(pw_entry[0])+1));
    strncpy(pwbuf->pw_name, pw_entry[0], strlen(pw_entry[0])+1);

    /* Copy password */
    pwbuf->pw_passwd = malloc(sizeof(char) * (strlen(pw_entry[1])+1));
    strncpy(pwbuf->pw_passwd, pw_entry[1], strlen(pw_entry[1])+1);

    /* Copy and convert to int UID and GID */
    pwbuf->pw_uid = (uid_t)atoi(pw_entry[2]);
    pwbuf->pw_gid = (gid_t)atoi(pw_entry[3]);

    /* Copy GECOS field */
    pwbuf->pw_gecos = malloc(sizeof(char) * (strlen(pw_entry[4])+1));
    strncpy(pwbuf->pw_gecos, pw_entry[4], strlen(pw_entry[4])+1);

    /* Copy home directory */
    pwbuf->pw_dir = malloc(sizeof(char) * (strlen(pw_entry[5])+1));
    strncpy(pwbuf->pw_dir, pw_entry[5], strlen(pw_entry[5])+1);

    /* Copy Shell */
    pwbuf->pw_shell = malloc(sizeof(char) * (strlen(pw_entry[6])+1));
    strncpy(pwbuf->pw_shell, pw_entry[6], strlen(pw_entry[6])+1);

    return status;
}

enum nss_status _nss_exfiles_getpwuid_r (uid_t uid,
                                        struct passwd *pwbuf,
                                        char *buffer,
                                        size_t buflen, 
                                        int *errnop)
{
    /* Default status */
    enum nss_status status = NSS_STATUS_NOTFOUND;

    _nss_exfiles_setpwent();
    while (NSS_STATUS_SUCCESS == _nss_exfiles_getpwent_r(pwbuf, 
                                                        NULL, 0, NULL)){
        if (uid == pwbuf->pw_uid) {
            status = NSS_STATUS_SUCCESS;
            break;
        }
    }
    _nss_exfiles_endpwent();
    return status;
}

enum nss_status _nss_exfiles_getpwnam_r (const char *pwnam,
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


