#include <check.h>
#include <stdlib.h>

#include "strsplit.h"

const char tosplit[] = "abc:1:345::sdfsdgggbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
 ":bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
 ":ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
 ":ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";

const char aitch9[] = "hhhhhhhhh";

START_TEST (strsplit_strcnt_basic)
{
    int h = 0;

    h = strcnt(aitch9, 'h');
    fail_unless(h == 9, "strcnt of 9 aitches");
}
END_TEST

START_TEST (strsplit_split_basic)
{
}
END_TEST

Suite * strsplit_suite(void) {
    Suite *s = suite_create("strsplit");
    TCase *tc_core = tcase_create("Core");

    suite_add_tcase(s, tc_core);
    tcase_add_test(tc_core, strsplit_strcnt_basic);
    tcase_add_test(tc_core, strsplit_split_basic);

    return s;
}

int main(void)
{

    int nf;

    Suite *s = strsplit_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;


/*
    char ** splat, ** splut;
    char spliton = ':';
    splut = splat = split(spliton, tosplit);

    while (NULL != *splat) {
        printf("p=%p s='%s'\n", *splat, *splat);
        ++splat;
    }

    split_free(splut);
*/
}
