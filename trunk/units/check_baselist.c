#include <check.h>
#include "list.h"
#include "gen/error_macros.h"
#include "check_funcs.h"
#ifndef RUNS
#define RUNS 100
#endif

START_TEST(test_baselist_create)
{
  List object;
  memset(&object, 0, sizeof(object));
  unsigned int x = 0;
  fail_unless(construct(List, NULL, sizeof(x), (x & 0x1) + 1) == EINVAL,
      "Failed to construct list object with invalid object");
  fail_unless(construct(List, &object, 0, (x & 0x1) + 1) == EINVAL,
      "Failed to construct list object with 0 size variable");
  fail_unless(construct(List, &object, sizeof(x), 0) == EINVAL,
      "Failed to construct list object with invalid flag");
  fail_unless(destruct(List, &object) == SUCCESS,
      "Failed to destruct list object");

}
END_TEST


START_TEST(test_baselist_destruct)
{
  List object;
  memset(&object, 0, sizeof(object));
  unsigned int x = 0;
  fail_unless(destruct(List, NULL) == EINVAL,
      "Failed to destruct list object");
  fail_unless(construct(List, &object, sizeof(x), 0) == EINVAL,
      "Failed to construct list object");
  fail_unless(destruct(List, &object) == SUCCESS,
      "Failed to destruct list object");

}
END_TEST

START_TEST(test_baselist_create_destruct_loop)
{
  List object;
  memset(&object, 0, sizeof(object));
  unsigned int x = 0;
  while (++x < RUNS) {
    fail_unless(construct(List, &object, sizeof(x), (x & 0x1) + 1) == SUCCESS,
        "Failed to construct list object on iteration %d",
        x);
    fail_unless(destruct(List, &object) == SUCCESS,
        "Failed to destruct list object on iteration %d",
        x);
  }
}
END_TEST

START_TEST(test_baselist_create_func)
{
  List object;
  memset(&object, 0, sizeof(object));
  unsigned int x = 0;
  fail_unless(construct_func(List, &object, sizeof(x), 
        FREEOBJ, NULL, NULL, NULL, NULL, NULL) == SUCCESS,
      "Failed to construct list object");
  fail_unless(destruct(List, &object) == SUCCESS,
      "Failed to destruct list object");
  fail_unless(set_alloc(List,  &object, ckalloc) == SUCCESS, NULL);
  fail_unless(set_dealloc(List,  &object, ckfree) == SUCCESS, NULL);
  fail_unless(set_compare(List,  &object, intcmp) == SUCCESS, NULL);
  fail_unless(set_print(List,  &object, print_int) == SUCCESS, NULL);
 

}
END_TEST

START_TEST(test_baselist_api_test)
{
  List object;
  memset(&object, 0, sizeof(object));
  unsigned int x = rand();
  unsigned int y = rand();
  fail_unless(construct(List, &object, sizeof(x), FREEOBJ) == SUCCESS, NULL);
  fail_unless(set_compare(List, &object, intcmp) == SUCCESS, NULL);
  fail_unless(push_back(List, &object, &x, STATIC) == SUCCESS, NULL);
  fail_unless(push_back(List, &object, &y, 0) == SUCCESS, NULL);
  fail_unless(pop_front(List, &object) == SUCCESS, NULL);
  fail_unless(size_of_List(&object) == 1, NULL);
  fail_unless(*(int*)front(List, &object) == y, NULL);
  fail_unless(clear_List(&object) == SUCCESS, NULL);
  fail_unless(!front_List(&object), NULL);
  fail_unless(destruct(List, &object) == SUCCESS, NULL);

}
END_TEST

Suite *
baselist_suite(void)
{
  Suite *s = suite_create("BaseList");
  /* Core test case */
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_baselist_create);
  tcase_add_test(tc_core, test_baselist_destruct);
  tcase_add_test(tc_core, test_baselist_create_destruct_loop);
  tcase_add_test(tc_core, test_baselist_create_func);
  tcase_add_test(tc_core, test_baselist_api_test);
  suite_add_tcase(s, tc_core);
  return s;
}
  int 
main(void)
{
  int number_failed;
  Suite *s = baselist_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
