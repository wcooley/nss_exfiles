
#include <dlfcn.h>
#include <nss.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

const char * NSS_EXFILES_LIB = "../src/.libs/libnss_exfiles.so.2.0.0";

void print_passwd_struct(FILE * outfile, const struct passwd * pwbuf) {
    fprintf(outfile, "%s:%s:%d:%d:%s:%s:%s\n",
            pwbuf->pw_name,
            pwbuf->pw_passwd,
            (int)pwbuf->pw_uid,
            (int)pwbuf->pw_gid,
            pwbuf->pw_gecos,
            pwbuf->pw_dir,
            pwbuf->pw_shell);
}

int main (void) 
{
    /*
    if (0 != __nss_configure_lookup("passwd", "exfiles")) {
        perror("Error configuring NSS");
        exit(1);
    }
    */

    void * handle;
    enum nss_status (*exfiles_getpwuid)(int, struct passwd *, char *, size_t, int *);
    struct passwd * p;
    char * dlerr;
    int * nss_errno;
    enum nss_status lookup_status;

    handle = dlopen(NSS_EXFILES_LIB, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    dlerror();

    *(void **) (&exfiles_getpwuid) = dlsym(handle, "_nss_exfiles_getpwuid_r");

    if (NULL != (dlerr = dlerror())) {
        fprintf(stderr, "%s\n", dlerr);
        exit(1);
    }

    p = malloc(sizeof(struct passwd));

    if (NULL == p) {
        perror("Error allocating memory for struct passwd");
        exit(1);
    }


    lookup_status = (*exfiles_getpwuid)(666, p, NULL, 0, nss_errno);

    if (NSS_STATUS_SUCCESS == lookup_status) {
        fprintf(stdout, "Looking up UID %d: ", 666);
        print_passwd_struct(stdout, p);
    }
    else
        fprintf(stderr, "getpwuid(%d, ...) failed\n", 666);

    lookup_status = (*exfiles_getpwuid)(1, p, NULL, 0, nss_errno);
    if (NSS_STATUS_SUCCESS == lookup_status) {
        fprintf(stdout, "Looking up UID %d: ", 1);
        print_passwd_struct(stdout, p);
    }
    else
        fprintf(stderr, "getpwuid(%d, ...) failed\n", 1);


/*
    p = getpwnam("wc00ley");
    if (NULL != p)
        print_passwd_struct(stderr, p);
    else
        fprintf(stderr, "getpwnam(\"wcOOley\") returned NULL\n");

    p = getpwuid(666);
    if (NULL != p)
        print_passwd_struct(stderr, p);
    else
        fprintf(stderr, "getpwnam(\"wcOOley\") returned NULL\n");
*/

    dlclose(handle);
    return 0;
}
