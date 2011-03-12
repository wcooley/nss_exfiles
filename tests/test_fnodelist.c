
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
    struct fnodelist_item *n = NULL;

    n = fnodelist_new_item();

    fail_unless(NULL != n, "Item not allocated successfully");
    fail_unless(NULL == n->next, "Item's /next/ not initialized correctly");
    fail_unless(NULL == n->node, "Item's /node/ not initialized correctly");

    fnodelist_destroy_item(n);
}
END_TEST

/* FIXME fnode test
START_TEST (test_fnodelist_new_item_str)
{
    struct fnodelist_item *n = NULL, *n2 = NULL;

    n = fnodelist_new_item();
    fail_unless(NULL != n, "Node not allocated successfully");

    n2 = fnode_set_path(n, teststr);

    fail_unless(NULL != n2, "Error setting path");
    fail_unless(0 == strcmp(n2->node->path, teststr), 
            "Set and test paths differ");

    n2 = fnodelist_item_set_str(n, NULL);
    fail_unless(NULL != n2, "Error setting string to NULL");
    fail_unless(NULL == n->node->path, "Error setting string to NULL");
}
END_TEST
*/

START_TEST (test_fnodelist_append_1node)
{
    struct fnodelist *l = NULL;
    struct fnodelist_item *n1 = NULL;
    struct fnodelist_item *n2 = NULL;

    l = fnodelist_new_list();
    n1 = fnodelist_new_item();

    fail_unless(NULL != l, "List not allocated successfully");

    n2 = fnodelist_append_item(l, n1);

    fail_unless(n2 == n1, "Node not appended correctly?!?");
    fail_unless(l->head == n1, "Node #1 not head?!?");

    fnodelist_destroy_list(l);
}
END_TEST

START_TEST (test_fnodelist_append_2nodes)
{
    struct fnodelist *l = NULL;
    struct fnodelist_item *nodes[2];
    struct fnodelist_item *tmpnode;

    nodes[0] = NULL;
    nodes[1] = NULL;

    l = fnodelist_new_list();

    fail_unless(NULL != l, "List not allocated successfully");

    nodes[0] = fnodelist_new_item();
    nodes[1] = fnodelist_new_item();

    tmpnode = fnodelist_append_item(l, nodes[0]);

    fail_unless(nodes[0] == tmpnode, "Node not appended correctly");
    fail_unless(l->head == nodes[0], "Node #1 not head");

    tmpnode = fnodelist_append_item(l, nodes[1]);

    fail_unless(tmpnode == nodes[1], "Node not appended correctly");
    fail_unless(nodes[0]->next == nodes[1], "Node #2 not next?!?");
    fail_unless(l->head->next == nodes[1], "Node #2 not head->next?!?");

    fnodelist_destroy_list(l);
}
END_TEST

START_TEST (test_fnodelist_append_path)
{
    struct fnodelist *l = NULL;
    struct fnodelist_item *n = NULL;
    int lenstr = 0;

    lenstr = strlen(teststr) + 1;
    l = fnodelist_new_list();

    fail_unless(NULL != l, "List not allocated successfully");

    n = fnodelist_append_path(l, teststr);

    fail_unless(NULL != n, "String/node not appended successfully");
    fail_unless(0 == strncmp(teststr, n->node->path, lenstr), 
            "String/node does not match");

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
  tcase_add_test(tc_core, test_fnodelist_append_1node);
  tcase_add_test(tc_core, test_fnodelist_append_2nodes);
  tcase_add_test(tc_core, test_fnodelist_append_path);
/*  tcase_add_test(tc_core, test_fnodelist_new_item_str); */

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
