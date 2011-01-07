/*************************************************************************
 * password functions
 *************************************************************************/

#include <errno.h>
#include <nss.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "exfiles-util-pwd.h"
#include "config.h"



/*
 * Utility for allocating memory for items in struct passwd based on string
 * array from strsplit.
 */
int
exfiles_alloc_passwd_from_pw_entry(struct passwd *pwbuf, char **pw_entry)
{
    /* Allocate storage for each string */
    pwbuf->pw_name      = malloc(sizeof(char) *(strlen(pw_entry[0])+1));
    pwbuf->pw_passwd    = malloc(sizeof(char) *(strlen(pw_entry[1])+1));
    pwbuf->pw_gecos     = malloc(sizeof(char) *(strlen(pw_entry[4])+1));
    pwbuf->pw_dir       = malloc(sizeof(char) *(strlen(pw_entry[5])+1));
    pwbuf->pw_shell     = malloc(sizeof(char) *(strlen(pw_entry[6])+1));

    if (  pwbuf->pw_name    == NULL
       || pwbuf->pw_passwd  == NULL
       || pwbuf->pw_gecos   == NULL
       || pwbuf->pw_dir     == NULL
       || pwbuf->pw_shell   == NULL
    )
        return -1;

    return 0;
}

/*
 * Utility to handle copying items from the pw_entry array into the struct
 * passwd.  Note that it should also be possible to simply update the struct
 * passwd pointers.  Consider that for future optimization.
 */
int
exfiles_copy_passwd_from_pw_entry(struct passwd *pwbuf, char **pw_entry)
{

    int tmplen = 0;     /* temp var for length of each string */

    /* Copy username */
    tmplen = strlen(pw_entry[0]);
    strncpy(pwbuf->pw_name, pw_entry[0], tmplen+1);

    /* FIXME Why did I put this in? */
    if (tmplen != strlen(pw_entry[0]))
        return -1;

    /* Copy password */
    tmplen = strlen(pw_entry[1]);
    strncpy(pwbuf->pw_passwd, pw_entry[1], tmplen+1);

    if (tmplen != strlen(pw_entry[1]))
        return -1;

    /* Copy and convert to int UID and GID */
    pwbuf->pw_uid = (uid_t)atoi(pw_entry[2]);
    pwbuf->pw_gid = (gid_t)atoi(pw_entry[3]);

    /* Copy GECOS field */
    tmplen = strlen(pw_entry[4]);
    strncpy(pwbuf->pw_gecos, pw_entry[4], tmplen+1);

    if (tmplen != strlen(pw_entry[4]))
        return -1;

    /* Copy home directory */
    tmplen = strlen(pw_entry[5]);
    strncpy(pwbuf->pw_dir, pw_entry[5], tmplen+1);

    if (tmplen != strlen(pw_entry[5]))
        return -1;

    /* Copy Shell */
    tmplen = strlen(pw_entry[6]);
    strncpy(pwbuf->pw_shell, pw_entry[6], tmplen+1);

    if (tmplen != strlen(pw_entry[6]))
        return -1;

    return 0;
}

/*
 * Utility for destroying the contents of a struct passwd.
 */
void
exfiles_passwd_destroy(struct passwd *pwbuf)
{
    if ( NULL != pwbuf ) {
        if ( NULL != pwbuf->pw_shell ) {
            free(pwbuf->pw_shell);
            pwbuf->pw_shell = NULL;
        }

        if ( NULL != pwbuf->pw_dir ) {
            free(pwbuf->pw_dir);
            pwbuf->pw_dir = NULL;
        }

        if ( NULL != pwbuf->pw_gecos ) {
            free(pwbuf->pw_gecos);
            pwbuf->pw_gecos = NULL;
        }

        if ( NULL != pwbuf->pw_passwd ) {
            free(pwbuf->pw_passwd);
            pwbuf->pw_passwd = NULL;
        }

        if ( NULL != pwbuf->pw_name ) {
            free(pwbuf->pw_name);
            pwbuf->pw_name = NULL;
        }

        /* This often wraps around and results in a large int that is
         * usually treated as "nobody"; rather of an arbitrary thing to do,
         * but it at least is better than defaulting to root's ID (0) */
        pwbuf->pw_uid = (uid_t) -1;
        pwbuf->pw_gid = (gid_t) -1;
    }
}

/*
 * User-friendly print of passwd struct contents.
 */
int
pretty_print_passwd_struct(FILE *outstream, const struct passwd *pwbuf)
{
    return fprintf(outstream,
                "Username:  '%s'\n"
                "Password:  '%s'\n"
                "UID:       '%d'\n"
                "GID:       '%d'\n"
                "GECOS:     '%s'\n"
                "Home dir:  '%s'\n"
                "Shell:     '%s'\n",
            pwbuf->pw_name,
            pwbuf->pw_passwd,
            (int)pwbuf->pw_uid,
            (int)pwbuf->pw_gid,
            pwbuf->pw_gecos,
            pwbuf->pw_dir,
            pwbuf->pw_shell
    );
}

/*
 * passwd file-like output
 */
int
print_passwd_struct(FILE *outstream, const struct passwd *pwbuf)
{
    return fprintf(outstream,
                "%s:%s:%d:%d:%s:%s:%s\n",
            pwbuf->pw_name,
            pwbuf->pw_passwd,
            (int)pwbuf->pw_uid,
            (int)pwbuf->pw_gid,
            pwbuf->pw_gecos,
            pwbuf->pw_dir,
            pwbuf->pw_shell);
}

/*
 * Deep compare of passwd structures.  There really isn't a necessarily
 * logical way to order them and we really need this for tests, so just return
 * true or false.  (erm, 1 or 0)
 */

int
exfiles_passwd_cmp(const struct passwd *pwbuf1, const struct passwd *pwbuf2)
{
    return
            (0 == strcmp(pwbuf1->pw_name,   pwbuf2->pw_name)    )
      &&    (0 == strcmp(pwbuf1->pw_passwd, pwbuf2->pw_passwd)  )
      &&    (0 == strcmp(pwbuf1->pw_gecos,  pwbuf2->pw_gecos)   )
      &&    (0 == strcmp(pwbuf1->pw_dir,    pwbuf2->pw_dir)     )
      &&    (0 == strcmp(pwbuf1->pw_shell,  pwbuf2->pw_shell)   )
      &&    (pwbuf1->pw_uid == pwbuf2->pw_uid)
      &&    (pwbuf1->pw_gid == pwbuf2->pw_gid)
      ;

}

