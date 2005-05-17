#include "nss_exfiles.h"

EXFILE_FILE(passwd)

static FILE * ex_passwd_f;


enum nss_status _nss_exfiles_setpwent(void) {
    enum nss_status status = NSS_STATUS_SUCCESS;

    ex_passwd_f = fopen(ex_passwd, "r");

    if (NULL == ex_passwd_f)
        status = NSS_STATUS_UNAVAIL;

    return status;
}

enum nss_status _nss_exfiles_endpwent(void) {
    enum nss_status status = NSS_STATUS_SUCCESS;

    if (NULL != ex_passwd_f)
        fclose(ex_passwd_f);

    return status;
}

/*
int get_pw_name(struct passwd *pwbuf, const char * pw_entry) {
    int slen;

    slen = strcspn(pw_entry, ":");
    pwbuf->pw_name = (char *)malloc(sizeof(char) * (slen+1));
    memcpy(pwbuf->pw_name, pw_entry, sizeof(char) * slen);
    pwbuf->pw_name[slen+1] = '\0';

    return 0; 
    
}

int get_pw_passwd(struct passwd *pwbuf, const char * pw_entry) {
    int slen;
    char * t1, t2;

    slen = strcspn(pw_entry, ":");

}

int split_string(char ** pw_entry_strs, char * str) {
    int slen; 
    int str_cnt = 0;
    char * t1;

    pw_entry_strs[str_cnt] = strtok(str, ":\n");

    while (NULL != pw_entry_strs[str_cnt]) {
        pw_entry_strs[++str_cnt] = strtok(NULL, ":\n");
    }

    return str_cnt;

}
*/

enum nss_status _nss_exfiles_getpwent_r (struct passwd *pwbuf, 
                                        char *buffer, size_t buflen, 
                                        int *errnop)
{
    enum nss_status status = NSS_STATUS_SUCCESS;
    int ret = 0;
    char * pw_entry = NULL;
    char * tmp;
    char * ptrptr[1024];
    size_t pw_ent_len = 0;
    int slen;
    char pw_entry_strs[7];
    struct passwd *pwp;

    pwp = fgetpwent(ex_passwd_f);

    if (NULL == pwp)
        status = NSS_STATUS_NOTFOUND;
    else
        memcpy(pwbuf, pwp, sizeof(struct passwd));
    
    return status;
}

enum nss_status _nss_exfiles_getpwuid_r (uid_t uid,
                                        struct passwd *pwbuf,
                                        char *buffer, size_t buflen, 
                                        int *errnop)
{
    enum nss_status status = NSS_STATUS_NOTFOUND;
    struct passwd pw;

    _nss_exfiles_setpwent();
    while (NSS_STATUS_SUCCESS == _nss_exfiles_getpwent_r(pwbuf, NULL, 0, NULL)){
        if(uid == pwbuf->pw_uid) {
            status = NSS_STATUS_SUCCESS;
            break;
        }
    }
    _nss_exfiles_endpwent();
    return status;
}

enum nss_status _nss_exfiles_getpwnam_r (const char *pwnam,
                                        struct passwd *pwbuf, 
                                        char *buffer, size_t buflen, 
                                        int *errnop)
{
    enum nss_status status = NSS_STATUS_NOTFOUND;
    int slen;

    slen = strlen(pwnam);

    _nss_exfiles_setpwent();
    while (NSS_STATUS_SUCCESS == _nss_exfiles_getpwent_r(pwbuf, NULL, 0, NULL)){
        if(0 == strncmp(pwnam, pwbuf->pw_name, slen)) {
            status = NSS_STATUS_SUCCESS;
            break;
        }
    }
    _nss_exfiles_endpwent();
    return status;
}
