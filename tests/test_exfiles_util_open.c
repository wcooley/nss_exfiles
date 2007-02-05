
#include <check.h>
#include <limits.h>
#include <nss.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

#include "exfiles-util.h"

enum nss_status status;
FILE * fhandle = NULL;
char * good_testfile = "/etc/hosts"; /* Test file that can be nearly 
                                        guaranteed to exist and be readable */

char * bad_testfile = "/XXXXlksjdflskdfsldkfjsflkj"; /* Shouldn't exist */

START_TEST(t_status_success)
{
    fail_unless(status == NSS_STATUS_SUCCESS, "Return status is NSS_STATUS_SUCCESS");
}
END_TEST

START_TEST(t_fhandle)
{
    fail_unless(fhandle != NULL, "File handle should not be NULL");
}
END_TEST

START_TEST(t_read_from_fhandle)
{
    char * result;
    char linebuf[MAX_CANON];

    result = fgets(linebuf, MAX_CANON, fhandle);

    /* fprintf(stderr, "\nlinebuf: '%s'\n", linebuf); */

    fail_unless(result != NULL, "fgets should not return NULL");
}
END_TEST

START_TEST(t_failure_fhandle)
{
    fail_unless(fhandle == NULL, "File handle should be NULL");
}
END_TEST

START_TEST(t_failure_status)
{
    fail_unless(status != NSS_STATUS_SUCCESS, 
                "Return status should not be NSS_STATUS_SUCCESS");
}
END_TEST

void success_setup(void) {
    status = exfiles_open_file(good_testfile, &fhandle);
}

void failure_setup(void) {
    status = exfiles_open_file(bad_testfile, &fhandle);
}

/*
 * Setup the libcheck test suite
 */
Suite * 
utils_suite(void) 
{
    Suite *s            = suite_create("utils");
    TCase * tc_success  = tcase_create("Success");
    TCase * tc_failure  = tcase_create("Failure");

    suite_add_tcase(s, tc_success);
    tcase_add_checked_fixture(tc_success, success_setup, NULL);
    tcase_add_test(tc_success, t_status_success);
    tcase_add_test(tc_success, t_fhandle);
    tcase_add_test(tc_success, t_read_from_fhandle);

    suite_add_tcase(s, tc_failure);
    tcase_add_checked_fixture(tc_failure, failure_setup, NULL);
    tcase_add_test(tc_failure, t_failure_fhandle);
    tcase_add_test(tc_failure, t_failure_status);

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
