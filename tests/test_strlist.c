
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strlist.h"

const char *teststr = "Now is the time for all good boys to go to bed.\n";

START_TEST (strlist_new_list)
{
    strlist *l = NULL;
        
    l = strlist_create_list();

    fail_unless(NULL != l, "List not allocated successfully");
    fail_unless(NULL == l->head, "List's /head/ not initialized correctly");

    strlist_destroy_list(l);
}
END_TEST

START_TEST (strlist_new_node)
{
    strlist_node *n = NULL;

    n = strlist_create_node();

    fail_unless(NULL != n, "Node not allocated successfully");
    fail_unless(NULL == n->next, "Node's /next/ not initialized correctly");
    fail_unless(NULL == n->string, "Node's /string/ not initialized correctly");

    strlist_destroy_node(n);
}
END_TEST

START_TEST (strlist_new_node_str)
{
    strlist_node *n = NULL, *n2 = NULL;

    n = strlist_create_node();
    fail_unless(NULL != n, "Node not allocated successfully");

    n2 = strlist_node_set_str(n, teststr);

    fail_unless(NULL != n2, "Error setting string");
    fail_unless(0 == strcmp(n2->string, teststr), 
            "Set and test strings differ");

    n2 = strlist_node_set_str(n, NULL);
    fail_unless(NULL != n2, "Error setting string to NULL");
    fail_unless(NULL == n->string, "Error setting string to NULL");
}
END_TEST

START_TEST (strlist_append_1node)
{
    strlist *l = NULL;
    strlist_node *n1 = NULL;
    strlist_node *n2 = NULL;

    l = strlist_create_list();
    n1 = strlist_create_node();

    fail_unless(NULL != l, "List not allocated successfully");

    n2 = strlist_append_node(l, n1);

    fail_unless(n2 == n1, "Node not appended correctly?!?");
    fail_unless(l->head == n1, "Node #1 not head?!?");

    strlist_destroy_list(l);
}
END_TEST

START_TEST (strlist_append_2nodes)
{
    strlist *l = NULL;
    strlist_node *nodes[2];
    strlist_node *tmpnode;

    nodes[0] = NULL;
    nodes[1] = NULL;

    l = strlist_create_list();

    fail_unless(NULL != l, "List not allocated successfully");

    nodes[0] = strlist_create_node();
    nodes[1] = strlist_create_node();

    tmpnode = strlist_append_node(l, nodes[0]);

    fail_unless(nodes[0] == tmpnode, "Node not appended correctly");
    fail_unless(l->head == nodes[0], "Node #1 not head");

    tmpnode = strlist_append_node(l, nodes[1]);

    fail_unless(tmpnode == nodes[1], "Node not appended correctly");
    fail_unless(nodes[0]->next == nodes[1], "Node #2 not next?!?");
    fail_unless(l->head->next == nodes[1], "Node #2 not head->next?!?");

    strlist_destroy_list(l);
}
END_TEST

START_TEST (strlist_append_string)
{
    strlist *l = NULL;
    strlist_node *n = NULL;
    int lenstr = 0;

    lenstr = strlen(teststr) + 1;
    l = strlist_create_list();

    fail_unless(NULL != l, "List not allocated successfully");

    n = strlist_append_str(l, teststr);

    fail_unless(NULL != n, "String/node not appended successfully");
    fail_unless(0 == strncmp(teststr, n->string, lenstr), 
            "String/node does not match");

    strlist_destroy_list(l);
}
END_TEST


Suite *
strlist_suite(void)
{
  Suite *s = suite_create("strlist");
  TCase *tc_core = tcase_create("Core");

  suite_add_tcase (s, tc_core);
  tcase_add_test(tc_core, strlist_new_list);
  tcase_add_test(tc_core, strlist_new_node);
  tcase_add_test(tc_core, strlist_append_1node);
  tcase_add_test(tc_core, strlist_append_2nodes);
  tcase_add_test(tc_core, strlist_append_string);
  tcase_add_test(tc_core, strlist_new_node_str);

  return s;
}

int 
main(void)
{
  int nf;
  Suite *s = strlist_suite();
  SRunner *sr = srunner_create(s);
  /* srunner_set_log(sr, "test.log"); */
  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
