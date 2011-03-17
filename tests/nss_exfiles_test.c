
#include <stdio.h>
#include <nss.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>


void print_passwd_struct(FILE * outstream, const struct passwd * pwbuf) {
    fprintf(outstream, "%s:%s:%d:%d:%s:%s:%s\n",
            pwbuf->pw_name,
            pwbuf->pw_passwd,
            pwbuf->pw_uid,
            pwbuf->pw_gid,
            pwbuf->pw_gecos,
            pwbuf->pw_dir,
            pwbuf->pw_shell);
}

int main (void) 
{
    fprintf(stderr, "Configuring exfiles password lookup...\n");
    if (-1 == __nss_configure_lookup("passwd", "exfiles")) {
        perror("Error configuring NSS");
        exit(1);
    }

    struct passwd * p;

    /* fprintf(stderr, "Calling setpwent()...\n"); */
    setpwent();

    do {
        /* fprintf(stderr, "Calling getpwent()...\n"); */
        p = getpwent();
        if (NULL == p) {
            /*fprintf(stderr, "getpwent() returned NULL\n");*/
            break;
        }

        print_passwd_struct(stderr, p);
    }
    while (NULL != p); 

    /* fprintf(stderr, "Calling endpwent()...\n"); */
    endpwent();
    return 0;
}
