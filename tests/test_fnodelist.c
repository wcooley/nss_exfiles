
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fnodelist.h"

const char *teststr = "Now is the time for all good boys to go to bed.\n";

START_TEST (test_fnodelist_new_list)
{
    struct fnodelist *l = NULL;
        
    l = fnodelist_new_list();

    fail_unless(NULL != l, "List not allocated successfully");
    fail_unless(NULL == l->head, "List's /head/ not initialized correctly");

    fnodelist_destroy_list(l);
}
END_TEST

START_TEST (test_fnodelist_new_item)
{
    struct fnodelist_item *item = NULL;

    item = fnodelist_new_item();

    fail_unless(NULL != item, "Item not allocated successfully");
    fail_unless(NULL == item->next, "Item's /next/ not initialized correctly");
    fail_unless(NULL == item->node, "Item's /node/ not initialized correctly");

    fnodelist_destroy_item(item);
}
END_TEST

START_TEST (test_fnodelist_append_1item)
{
    struct fnodelist *l = NULL;
    struct fnodelist_item *item1 = NULL, *item2 = NULL;

    l = fnodelist_new_list();
    item1 = fnodelist_new_item();

    fail_unless(NULL != l, "List not allocated successfully");

    item2 = fnodelist_append_item(l, item1);

    fail_unless(item2 == item1, "Item not appended correctly?!?");
    fail_unless(l->head == item1, "Item #1 not head?!?");

    fnodelist_destroy_list(l);
}
END_TEST

START_TEST (test_fnodelist_append_2items)
{
    struct fnodelist *l = NULL;
    struct fnodelist_item *items[2];
    struct fnodelist_item *tmpitem;

    items[0] = NULL;
    items[1] = NULL;

    l = fnodelist_new_list();

    fail_unless(NULL != l, "List not allocated successfully");

    items[0] = fnodelist_new_item();
    items[1] = fnodelist_new_item();

    tmpitem = fnodelist_append_item(l, items[0]);

    fail_unless(items[0] == tmpitem, "Item not appended correctly");
    fail_unless(l->head == items[0], "Item #1 not head");

    tmpitem = fnodelist_append_item(l, items[1]);

    fail_unless(tmpitem == items[1], "Item not appended correctly");
    fail_unless(items[0]->next == items[1], "Item #2 not next?!?");
    fail_unless(l->head->next == items[1], "Item #2 not head->next?!?");

    fnodelist_destroy_list(l);
}
END_TEST

START_TEST (test_fnodelist_append_fnode)
{
    struct fnodelist *list = NULL;
    struct fnodelist_item *item = NULL;
    struct fnode *fn = NULL;

    list = fnodelist_new_list();
    fail_unless(NULL != list, "fnodelist not allocated successfully");

    fn = fnode_new();
    fail_unless(NULL != fn, "fnode not allocated successfully");

    item = fnodelist_append_fnode(list, fn);
    fail_unless(NULL != item, "Item not allocated successfully");
}
END_TEST

START_TEST (test_fnodelist_append_path)
{
    struct fnodelist *l = NULL;
    struct fnodelist_item *item = NULL;
    int lenstr = 0;

    lenstr = strlen(teststr) + 1;
    l = fnodelist_new_list();

    fail_unless(NULL != l, "List not allocated successfully");

    item = fnodelist_append_path(l, teststr);

    fail_unless(NULL != item, "Path/node not appended successfully");
    fail_unless(0 == strncmp(teststr, item->node->path, lenstr), 
            "Path/node does not match");

    fnodelist_destroy_list(l);
}
END_TEST


Suite *
fnodelist_suite(void)
{
  Suite *s = suite_create("fnodelist");
  TCase *tc_core = tcase_create("Core");

  suite_add_tcase (s, tc_core);
  tcase_add_test(tc_core, test_fnodelist_new_list);
  tcase_add_test(tc_core, test_fnodelist_new_item);
  tcase_add_test(tc_core, test_fnodelist_append_1item);
  tcase_add_test(tc_core, test_fnodelist_append_2items);
  tcase_add_test(tc_core, test_fnodelist_append_fnode);
  tcase_add_test(tc_core, test_fnodelist_append_path);

  return s;
}

int 
main(void)
{
  int nf;
  Suite *s = fnodelist_suite();
  SRunner *sr = srunner_create(s);
  /* srunner_set_log(sr, "test.log"); */
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
