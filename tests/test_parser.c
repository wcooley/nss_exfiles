#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exfiles-conf-parser.h"

#define REFERENCE_CONF "../test-data/exfiles-conf"

/* From a later version of 'check' than is packaged for RHEL5 */
#ifndef ck_assert_msg
#define ck_assert_msg fail_unless
/* String comparsion macros with improved output compared to fail_unless() */
#define _ck_assert_str(C, X, O, Y) ck_assert_msg(C, \
        "Assertion '"#X#O#Y"' failed: "#X"==\"%s\", "#Y"==\"%s\"", X, Y)
#define ck_assert_str_eq(X, Y) _ck_assert_str(!strcmp(X, Y), X, ==, Y)
#define ck_assert_str_ne(X, Y) _ck_assert_str(strcmp(X, Y), X, !=, Y)
#endif /* ck_assert_msg */

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


struct exfiles_conf *reference_conf;

#define addpasswd(PFILE) (strlist_append_str(reference_conf->passwd, PFILE))
#define addgroup(GFILE)  (strlist_append_str(reference_conf->group, GFILE))

void setup_reference_conf(void) {

    reference_conf = calloc(1, sizeof(struct exfiles_conf));

    reference_conf->passwd = strlist_create_list();
    reference_conf->group  = strlist_create_list();

    addpasswd("/var/foo-pass");
    addpasswd("/etc/bar-pass");
    addpasswd("/bar/baz");
    addpasswd("sdlfs");
    addpasswd("/alt/binaries/pictures");

    addgroup("/tmp/group");
    addgroup("/nfs/groupie");
    addgroup("/bab/zab");
    addgroup("/tab/over-here");
}

void teardown_reference_conf(void) {
    /* FIXME */
}

void compare_lists(const char *type, strlist_node *strptr,
                    strlist_node *refstrptr) {

    char parsed_ran_out[64], ref_ran_out[64];

    sprintf(parsed_ran_out,
            "Parsed %s data ran out before reference", type );

    sprintf(ref_ran_out,
            "Reference %s data ran out before parsed", type );

    while( strptr != NULL || refstrptr != NULL ) {
        fail_if(strptr == NULL, parsed_ran_out);
        fail_if(refstrptr == NULL, ref_ran_out);
        ck_assert_str_eq( strptr->string, refstrptr->string );
        strptr = strptr->next;
        refstrptr = refstrptr->next;
    }
}

START_TEST(test_reference_conf_passwd)
{
    FILE *cfgfile;
    struct exfiles_conf conf;
    strlist_node *strptr, *refstrptr;

    cfgfile = fopen(REFERENCE_CONF, "r");

    fail_unless( exfiles_init_config(&conf) == 0,
                "error initializing exfiles_conf struct");

    fail_unless( exfiles_parse_config(cfgfile, &conf) == 0,
                "error parsing config file");

    strptr = (conf.passwd)->head;
    refstrptr = (reference_conf->passwd)->head;

    compare_lists("passwd", strptr, refstrptr);
}
END_TEST

START_TEST(test_reference_conf_group)
{
    FILE *cfgfile;
    struct exfiles_conf conf;
    strlist_node *strptr, *refstrptr;

    cfgfile = fopen(REFERENCE_CONF, "r");

    fail_unless( exfiles_init_config(&conf) == 0,
                "error initializing exfiles_conf struct");

    fail_unless( exfiles_parse_config(cfgfile, &conf) == 0,
                "error parsing config file");

    strptr = (conf.group)->head;
    refstrptr = (reference_conf->group)->head;

    compare_lists("group", strptr, refstrptr);
}
END_TEST

Suite *
parser_suite(void)
{
    Suite *tsuite = suite_create("parser");
    TCase *tc_null = tcase_create("Null");
    TCase *tc_ref = tcase_create("Reference");

    /* Null Conf */
    suite_add_tcase(tsuite, tc_null);
    tcase_add_test(tc_null, test_parser_null);

    /* Reference Conf */
    suite_add_tcase(tsuite, tc_ref);
    tcase_add_checked_fixture(tc_ref, setup_reference_conf,
                                teardown_reference_conf);
    tcase_add_test(tc_ref, test_reference_conf_passwd);
    tcase_add_test(tc_ref, test_reference_conf_group);

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


