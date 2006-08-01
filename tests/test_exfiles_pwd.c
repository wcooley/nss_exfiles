
#include <check.h>
#include <dlfcn.h>
#include <errno.h>
#include <nss.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * NSS library file to open and load.
 */
const char * NSS_EXFILES_LIB = "../src/.libs/libnss_exfiles.so.2.0.0";

/*
 * struct passwd array of entries from ../test-data/passwd
 */
const struct passwd t_pwd[] = {
    { "wcooley",    "asdfsdf",  1,      2, 
        "Me",                   "/home/wcooley", 
        "/usr/bin/ksh/or/another/really/long/path"
    },
    { "wc00ley",    "x",        666,    666, 
        "Wil Cooley",           "/home/wc00ley", 
        "/bin/bash" 
    },
    { "wc01ley",    "",         667,    667, 
        "Wil Cooley 1",         "/home/wc01ley", 
        "/bin/bash"
    },

    { NULL, NULL, 0, 0, NULL, NULL, NULL },
};

/*
 * pointers to dynamically-loaded functions
 */

enum nss_status (*exfiles_setpwent)(void);
enum nss_status (*exfiles_endpwent)(void);
enum nss_status (*exfiles_getpwent)(struct passwd *, char *, size_t, int *);
enum nss_status (*exfiles_getpwuid)(int, 
                                    struct passwd *, char *, size_t, int *);
enum nss_status (*exfiles_getpwnam)(const char *, 
                                    struct passwd *, char *, size_t, int *);

/* 
 * dynamic loader handle
 * global because it needs to be available in setup and teardown 
 */
void *dl_handle;

/*
 * Tests
 */

START_TEST(t_getpwent)
{
    struct passwd *p_buf;
    enum nss_status lookup_status;

    /* the passwd data is copied into this structure */
    p_buf = malloc(sizeof(struct passwd));

    fail_unless(NULL != p_buf, strerror(errno));

    int i = 0;

    /* FIXME */
    
}
END_TEST

START_TEST(t_getpwuid)
{
    int i;
    struct passwd *p_buf;
    enum nss_status lookup_status;

    /* getpwuid copies the data into this structure */
    p_buf = malloc(sizeof(struct passwd));
    fail_unless(NULL != p_buf, strerror(errno));

    for (i=0; t_pwd[i].pw_name != NULL; ++i) {
        lookup_status = (*exfiles_getpwuid)(
                t_pwd[i].pw_uid,
                p_buf,
                NULL, 0, NULL);

        /* Ensure a successful return */
        fail_unless(NSS_STATUS_SUCCESS == lookup_status, 
                    "Lookup unsuccessful");
        
        /* Ensure that the expected and received UIDs match */
        fail_unless(p_buf->pw_uid == t_pwd[i].pw_uid,
                    "UIDs do not match");

        /* Do a wholesale memory comparison of the structs
         * Uh, does this really do what I want?  Does it *really* do a 
         * deep comparision.  If not, why am I getting now errors?
         */
        fail_unless(memcmp(p_buf, &t_pwd[i], sizeof(struct passwd)),
                    "passwd structs differ");
    }
}
END_TEST

START_TEST(t_getpwent)
{
    /* FIXME */
}
END_TEST

/*
 * Main and auxillary functions
 */
void 
pwd_setup(void) 
{

    int i;
    char *dlerr;

    struct func_list {
        void *fpointer;
        char *fname; 
    };

    struct func_list funcs[] = {
        /* func pointer         symbol name                 */
        { &exfiles_setpwent,    "_nss_exfiles_setpwent"     },
        { &exfiles_endpwent,    "_nss_exfiles_endpwent"     },
        { &exfiles_getpwent,    "_nss_exfiles_getpwent_r"   },
        { &exfiles_getpwuid,    "_nss_exfiles_getpwuid_r"   },
        { &exfiles_getpwnam,    "_nss_exfiles_getpwnam_r"   },
        { NULL,                 NULL                        }
    };

    dl_handle = dlopen(NSS_EXFILES_LIB, RTLD_LAZY);
    
    if (!dl_handle)
        fail_unless(NULL != dl_handle, dlerror());

    /* clear as example in man page does */
    dlerror();

    for (i=0; NULL != funcs[i].fpointer; ++i) {
        /* FIXME The pointer casting is magical to me; I got it form the man
         * page and it works, but I need to take the time to understand it
         * */
        *(void **) (funcs[i].fpointer) = dlsym(dl_handle, funcs[i].fname);
        dlerr = dlerror();
        fail_unless(NULL == dlerr, dlerr);
    }

}

void 
pwd_teardown(void) 
{
    if(dl_handle)
        dlclose(dl_handle);
}

/*
 * Setup the libcheck test suite
 */
Suite * 
pwd_suite(void) 
{
    Suite *s        = suite_create("pwd");
    TCase * tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, pwd_setup, pwd_teardown);
    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, t_getpwuid);
    tcase_add_test(tc_core, t_getpwnam);


    return s;
}

/*
 * Create the suite runner and run the tests
 */
int 
do_tests(void) 
{
    int count_failed;

    SRunner *sr     = srunner_create(pwd_suite());
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
