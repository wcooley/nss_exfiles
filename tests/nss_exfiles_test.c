
#include <stdio.h>
#include <nss.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>


int main (void) 
{
    fprintf(stderr, "Configuring exfiles password lookup...\n");
    if (-1 == __nss_configure_lookup("passwd", "exfiles")) {
        perror("Error configuring NSS");
        exit(1);
    }

    struct passwd * p;

    fprintf(stderr, "Calling setpwent()...\n");
    setpwent();

    do {
        fprintf(stderr, "Calling getpwent()...\n");
        p = getpwent();
        if (NULL == p) break;

        fprintf(stderr, "p != NULL\n");
        printf("%s:%s:%d:%d\n", p->pw_name, p->pw_passwd, 
                (int)p->pw_uid, (int)p->pw_gid);
    }
    while (NULL != p); 

    fprintf(stderr, "Calling endpwent()...\n");
    endpwent();
    return 0;
}
