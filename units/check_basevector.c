#include <check.h>
#include "vector.h"
#include "gen/error_macros.h"
#include "check_funcs.h"
#ifndef RUNS
#define RUNS 100
#endif

START_TEST(test_basevector_create)
{
  Vector object;
  memset(&object, 0, sizeof(object));
  unsigned int x = 0;
  fail_unless(construct(Vector, NULL, sizeof(x), (x & 0x1) + 1) == EINVAL,
      "Failed to construct vector object");
  fail_unless(construct(Vector, &object, 0, (x & 0x1) + 1) == EINVAL,
      "Failed to construct vector object");
  fail_unless(construct(Vector, &object, sizeof(x), 0) == EINVAL,
      "Failed to construct vector object");
  fail_unless(destruct(Vector, &object) == SUCCESS,
      "Failed to destruct vector object");

}
END_TEST


START_TEST(test_basevector_destruct)
{
  Vector object;
  memset(&object, 0, sizeof(object));
  unsigned int x = 0;
  fail_unless(destruct(Vector, NULL) == EINVAL,
      "Failed to destruct vector object");
  fail_unless(construct(Vector, &object, sizeof(x), 0) == EINVAL,
      "Failed to construct vector object");
  fail_unless(destruct(Vector, &object) == SUCCESS,
      "Failed to destruct vector object");

}
END_TEST

START_TEST(test_basevector_create_destruct_loop)
{
  Vector object;
  memset(&object, 0, sizeof(object));
  unsigned int x = 0;
  while (++x < RUNS) {
    fail_unless(construct(Vector, &object, sizeof(x), (x & 0x1) + 1) == SUCCESS,
        "Failed to construct vector object on iteration %d",
        x);
    fail_unless(destruct(Vector, &object) == SUCCESS,
        "Failed to destruct vector object on iteration %d",
        x);
  }
}
END_TEST

START_TEST(test_basevector_create_func)
{
  Vector object;
  memset(&object, 0, sizeof(object));
  unsigned int x = 0;
  fail_unless(construct_func(Vector, &object, sizeof(x), 
        FREEOBJ, NULL, NULL, NULL, NULL, NULL) == SUCCESS,
      "Failed to construct vector object");
  fail_unless(destruct(Vector, &object) == SUCCESS,
      "Failed to destruct vector object");
  fail_unless(set_alloc(Vector,  &object, ckalloc) == SUCCESS, NULL);
  fail_unless(set_dealloc(Vector,  &object, ckfree) == SUCCESS, NULL);
  fail_unless(set_compare(Vector,  &object, intcmp) == SUCCESS, NULL);
  fail_unless(set_print(Vector,  &object, print_int) == SUCCESS, NULL);
 

}
END_TEST

START_TEST(test_basevector_api_test)
{
  Vector object;
  memset(&object, 0, sizeof(object));
  unsigned int x = rand();
  unsigned int y = rand();
  fail_unless(construct(Vector, &object, sizeof(x), FREEOBJ) == SUCCESS, NULL);
  fail_unless(set_compare(Vector, &object, intcmp) == SUCCESS, NULL);
  fail_unless(push_back(Vector, &object, &x, STATIC) == SUCCESS, NULL);
  fail_unless(insert_at_Vector(&object, &y, 0) == SUCCESS, NULL);
  fail_unless(size_of_Vector(&object) == 1, NULL);
  fail_unless(*(int*)return_at_Vector(&object, 0) == y, NULL);
  fail_unless(clear_Vector(&object) == SUCCESS, NULL);
  fail_unless(!return_at_Vector(&object, 0), NULL);
  fail_unless(destruct(Vector, &object) == SUCCESS, NULL);

}
END_TEST

Suite *
basevector_suite(void)
{
  Suite *s = suite_create("BaseVector");
  /* Core test case */
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_basevector_create);
  tcase_add_test(tc_core, test_basevector_destruct);
  tcase_add_test(tc_core, test_basevector_create_destruct_loop);
  tcase_add_test(tc_core, test_basevector_create_func);
  tcase_add_test(tc_core, test_basevector_api_test);
  suite_add_tcase(s, tc_core);
  return s;
}
  int 
main(void)
{
  int number_failed;
  Suite *s = basevector_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
