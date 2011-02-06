#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exfiles-conf-parser.h"

START_TEST (test_parser_null)
{
    FILE *cfgfile;
    struct exfiles_conf conf;

    cfgfile = fopen("/dev/null", "r");

    fail_unless( exfiles_init_config(&conf) == 0,
                "error initializing exfiles_conf struct");

    fail_unless( exfiles_parse_config(cfgfile, &conf) == 0,
                "error parsing config file");

    fail_unless( (conf.passwd)->head == NULL,
                "/dev/null input but passwd has non-null head node");

    fail_unless( (conf.group)->head == NULL,
                "/dev/null input but group has non-null head node");


}
END_TEST

Suite *
parser_suite(void)
{
    Suite *tsuite = suite_create("parser");
    TCase *tc_core = tcase_create("Core");

    suite_add_tcase(tsuite, tc_core);

    tcase_add_test(tc_core, test_parser_null);

    return tsuite;
}

int
main(void)
{
    int numfailed;
    Suite *tsuite = parser_suite();
    SRunner *srunner = srunner_create(tsuite);

    srunner_run_all(srunner, CK_NORMAL);
    numfailed = srunner_ntests_failed(srunner);
    srunner_free(srunner);

    return (numfailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}

/* Quick & dirty manual test of parser for now */

/*
extern FILE *_nss_exfiles_in;
extern int _nss_exfiles_lineno, _nss_exfiles_debug;

int main(int argc, const char* argv[]) {
    _nss_exfiles_in = fopen(argv[1], "r");
    _nss_exfiles_debug=0;
    do {
        _nss_exfiles_parse();
    } while (!feof(_nss_exfiles_in));

    return 0;
}

*/


