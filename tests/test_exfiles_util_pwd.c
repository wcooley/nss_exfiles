
#include <check.h>
#include <errno.h>
#include <nss.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>

#include "exfiles-util.h"
#include "exfiles-util-pwd.h"

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
        "/bin/bash1"
    },

    { NULL, NULL, 0, 0, NULL, NULL, NULL },
};
/* Copy of the above to exercise the comparison */
const struct passwd t2_pwd[] = {
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
        "/bin/bash1"
    },

    { NULL, NULL, 0, 0, NULL, NULL, NULL },
};


START_TEST(t_exfiles_passwd_cmp)
{

    int i;

    for (i=0; NULL != t2_pwd[i].pw_name; ++i) {
        fail_unless(exfiles_passwd_cmp(&t2_pwd[i], &t_pwd[i]),
                "False negative comparison");
    }
}
END_TEST

START_TEST(t_exfiles_passwd_cmp_fail)
{
    /* Should NOT match */
    fail_unless(! exfiles_passwd_cmp(&t2_pwd[0], &t_pwd[1]));
}
END_TEST

/*
 * Setup the libcheck test suite
 */
Suite * 
utils_suite(void) 
{
    Suite *s        = suite_create("utils");
    TCase * tc_core = tcase_create("Core");

    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, t_exfiles_passwd_cmp);
    tcase_add_test(tc_core, t_exfiles_passwd_cmp_fail);

    return s;
}

/*
 * Create the suite runner and run the tests
 */
int 
do_tests(void) 
{
    int count_failed;

    SRunner *sr     = srunner_create(utils_suite());
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
