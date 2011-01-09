#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
START_TEST (parser_null)
{
    FILE *_nss_exfiles_in;
    int yyret;

    _nss_exfiles_in = fopen("/dev/null", "r");
    _nss_exfiles_debug=1;

    yyret = _nss_exfiles_parse();
}
END_TEST

Suite *
parser_suite(void)
{
    Suite *tsuite = suite_create("parser");
    TCase *tc_core = tcase_create("Core");

    suite_add_tcase(tsuite, tc_core);

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
*/
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


