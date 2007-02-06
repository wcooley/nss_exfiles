
#include <check.h>
#include <dlfcn.h>
#include <errno.h>
#include <nss.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

#include "exfiles-util-grp.h"

/*
 * NSS library file to open and load.
 */
const char * NSS_EXFILES_LIB = "../src/.libs/libnss_exfiles.so.2.0.0";

/*
 * struct group array of entries from ../test-data/group
 */

char * grp_mem[] = { "wcooley", NULL };

const struct group t_grp[] = {
    { "wcooley",    "*",    500,    NULL },
    { "users",      "*",    100,    grp_mem },
    { "cooleys",    "*",    1506,   grp_mem }, 
/*    { "users",      "*",    100,    { "wcooley", NULL }},
    { "cooleys",    "*",    1506,   { "wcooley", NULL }}, */

    { NULL, NULL, 0, NULL },
};

enum nss_status (*exfiles_setgrent)(void);
enum nss_status (*exfiles_endgrent)(void);
enum nss_status (*exfiles_getgrent)(struct group *, char *, size_t, int *);
enum nss_status (*exfiles_getgrgid)(int,
                                    struct group *, char *, size_t, int *);
enum nss_status (*exfiles_getgrnam)(const char *,
                                    struct group *, char *, size_t, int *);
void (*set_group_file)(char *);

/* 
 * dynamic loader handle
 * global because it needs to be available in setup and teardown 
 */
void *dl_handle;


/*
 * Tests
 */



/*
 * Main and auxillary functions
 */

void
grp_setup(void)
{

    int i;
    char *dlerr;

    struct func_list {
        void *fpointer;
        char *fname; 
    };

    struct func_list funcs[] = {
        /* func pointer         symbol name                 */
        { &exfiles_setgrent,    "_nss_exfiles_setgrent"     },
        { &exfiles_endgrent,    "_nss_exfiles_endgrent"     },
        { &exfiles_getgrent,    "_nss_exfiles_getgrent_r"   },
        { &exfiles_getgrgid,    "_nss_exfiles_getgrgid_r"   },
        { &exfiles_getgrnam,    "_nss_exfiles_getgrnam_r"   },
        { &set_group_file,      "_set_group_file"           },
        { NULL,                 NULL                        }
    };

    dl_handle = dlopen(NSS_EXFILES_LIB, RTLD_LAZY);
    
    if (!dl_handle)
        fail_unless(NULL != dl_handle, dlerror());

    /* clear as example in man page does */
    dlerror();

    for (i=0; NULL != funcs[i].fpointer; ++i) {
        /* TODO The pointer casting is magical to me; I got it form the man
         * page and it works, but I need to take the time to understand it
         * */
        *(void **) (funcs[i].fpointer) = dlsym(dl_handle, funcs[i].fname);
        dlerr = dlerror();
        fail_unless(NULL == dlerr, dlerr);
    }

    set_group_file("../test-data/group");

}

void
grp_teardown(void)
{
    if(dl_handle)
        dlclose(dl_handle);
}


/*
 * Setup the libcheck test suite
 */
Suite * 
grp_suite(void)
{
    Suite *s        = suite_create("grp");
    TCase *tc_core  = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, grp_setup, grp_teardown);
    suite_add_tcase(s, tc_core);

    return s;
}

/*
 * Create the suite runner and run the tests
 */
int 
do_tests(void) 
{
    int count_failed;

    SRunner *sr     = srunner_create(grp_suite());
    srunner_run_all(sr, CK_NORMAL);

    count_failed    = srunner_ntests_failed(sr);
    srunner_free(sr);

    return count_failed;
}

int 
main(void) 
{
    int count_failed;

    count_failed = do_tests();

    return  (0 == count_failed) 
            ? EXIT_SUCCESS 
            : EXIT_FAILURE
            ;
}
