
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exfiles-util.h"
#include "fnodelist.h"

const char *teststr = "Now is the time for all good boys to go to bed.\n";

#define append_path_test(item, fnodelist, path)   \
    (item) = fnodelist_append_path((fnodelist), (path)); \
    fail_unless(NULL != (item), "Error appending path '" XSTR(path) "'");

#define fnodelist_new(list)         \
    (list) = fnodelist_new_list();  \
    fail_unless(NULL != (list), "Error allocating new list");

START_TEST (test_fnodelist_new_list)
{
    struct fnodelist *l = NULL;
        
    fnodelist_new(l);

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

    fnodelist_new(l);

    item1 = fnodelist_new_item();

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

    fnodelist_new(l);

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

    fnodelist_new(list);

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

    fnodelist_new(l);

    item = fnodelist_append_path(l, teststr);

    fail_unless(NULL != item, "Path/node not appended successfully");
    fail_unless(0 == strncmp(teststr, item->node->path, lenstr), 
            "Path/node does not match");

    fnodelist_destroy_list(l);
}
END_TEST

START_TEST(test_fnodelist_next_item)
{
    struct fnodelist *list = NULL;
    struct fnodelist_item *item[2], *itemt = NULL;

    fnodelist_new(list);

    append_path_test(item[0], list, "../test-data/passwd");
    append_path_test(item[1], list, "../test-data/group");

    itemt = fnodelist_next_item(list);

    fail_unless(itemt == item[0],
            "first 'next' item different from reference first item");

    itemt = fnodelist_next_item(list);

    fail_unless(itemt == item[1],
            "second 'next' item different from reference second item");

    itemt = fnodelist_next_item(list);

    fail_unless(itemt == NULL,
            "final next item pointer is not NULL");

    fnodelist_destroy_list(list);
}
END_TEST

START_TEST(test_fnodelist_next_fnode)
{
    struct fnodelist *list = NULL;
    struct fnode *ftmp = NULL;
    char *test_paths[] = {
        "../test-data/passwd",
        "../test-data/group"
    };

    fnodelist_new(list);

    fnodelist_append_path(list, test_paths[0]);
    fnodelist_append_path(list, test_paths[1]);

    ftmp = fnodelist_next_fnode(list);
    fail_unless(ftmp != NULL, "first 'next' fnode is NULL");
    fail_unless(0 == strncmp(test_paths[0], ftmp->path, strlen(test_paths[0])),
            "Path from first fnode not same as first test path");

    ftmp = fnodelist_next_fnode(list);
    fail_unless(ftmp != NULL, "second 'next' fnode is NULL");
    fail_unless(0 == strncmp(test_paths[1], ftmp->path, strlen(test_paths[1])),
            "Path from second fnode not same as first test path");

    ftmp = fnodelist_next_fnode(list);
    fail_unless(ftmp == NULL, "last 'next' fnode should be NULL");

    fnodelist_destroy_list(list);
}
END_TEST

START_TEST(test_fnodelist_fgets)
{
    struct fnodelist *list = NULL;
    int i = 0;
    char *test_paths[] = {
        "../test-data/passwd",
        "../test-data/group"
    };
    char *test_lines[] = {
        "wcooley:asdfsdf:1:2:Me:/home/wcooley:/usr/bin/ksh/or/another/really/long/path\n",
        "wc00ley:x:666:666:Wil Cooley:/home/wc00ley:/bin/bash\n",
        "wc01ley::667:667:Wil Cooley 1:/home/wc01ley:/bin/bash1\n",
        "wcooley:x:2:\n",
        "wc00ley:x:666:\n",
        "wc01ley:x:667:wc00ley\n",
    };
    char buf[1024];

    fnodelist_new(list);

    fnodelist_append_path(list, test_paths[0]);
    fnodelist_append_path(list, test_paths[1]);

    while(NULL != fnodelist_fgets(buf, 1024, list)) {
        fail_unless(0 == strcmp(test_lines[i], buf), 
                "Assertion failed: '%s' != '%s'", test_lines[i], buf);
        i++;
    }

    fnodelist_destroy_list(list);
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
  tcase_add_test(tc_core, test_fnodelist_next_item);
  tcase_add_test(tc_core, test_fnodelist_next_fnode);
  tcase_add_test(tc_core, test_fnodelist_fgets);

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
