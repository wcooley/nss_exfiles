
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fnode.h"

START_TEST (test_fnode_new)
{
    struct fnode *fn = NULL;

    fn = fnode_new();
    fail_unless(NULL != fn, "fnode not allocated correctly");
    fail_unless(NULL == fn->path, "fnode's path not initialized correctly");
    fail_unless(NULL == fn->handle, "fnode's handle not initialized correctly");
    fail_unless((time_t)0 == fn->mtime, "fnode's mtime not initialized correctly");

    fnode_destroy(fn);
}
END_TEST

START_TEST (test_fnode_set_path)
{
    struct fnode *fn = NULL, *fnr = NULL;
    char test_path[] = "/etc/hosts";
    char **fnpath = NULL;
    int pathlen = strlen(test_path);

    fn = fnode_new();
    fail_unless(NULL != fn, "fnode not allocated correctly");
    fail_unless(NULL == fn->path, "fnode's path not initialized correctly");

    fnr = fnode_set_path(fn, test_path);
    fail_unless(fnr == fn, "fnode returned by fnode_set_path not same as node param");
    fail_unless(0 == strncmp(fnr->path, test_path, (pathlen+1)),
                            "fnode's path not same as test path");

    /* ptr to fnode's path member */
    fnpath = &(fn->path);

    fnode_destroy(fn);

    fail_unless(NULL != fnpath, "destroyed path pointer not NULL");
    fail_unless(NULL != fn, "destroyed fnode pointer not NULL");

}
END_TEST

Suite *
fnode_suite(void)
{
  Suite *s = suite_create("fnode");
  TCase *tc_core = tcase_create("Core");

  suite_add_tcase (s, tc_core);
  tcase_add_test(tc_core, test_fnode_new);
  tcase_add_test(tc_core, test_fnode_set_path);

  return s;
}

int 
main(void)
{
  int nf;
  Suite *s = fnode_suite();
  SRunner *sr = srunner_create(s);
  /* srunner_set_log(sr, "test.log"); */
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
