#include "../s21_matrix.c"
#include "test_complements.c"
#include "test_create.c"
#include "test_determinant.c"
#include "test_eq.c"
#include "test_inverse.c"
#include "test_mult.c"
#include "test_subsum.c"
#include "test_trans.c"
#include "tests.h"

int main(void) {
  Suite *testcase = suite_s21_matrix_tests();
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return 0;
}

Suite *suite_s21_matrix_tests() {
  Suite *s = suite_create("suite_s21_matrix_tests");
  TCase *tc = tcase_create("s21_matrix_tests");

  tcase_add_loop_test(tc, create_and_free, 0, 100);
  tcase_add_loop_test(tc, create_wrong, 0, 100);
  tcase_add_loop_test(tc, same_matrixes, 0, 100);
  tcase_add_loop_test(tc, not_equal, 0, 100);
  tcase_add_loop_test(tc, not_equal2, 0, 100);
  tcase_add_loop_test(tc, sum, 0, 100);
  tcase_add_loop_test(tc, sub, 0, 100);
  tcase_add_loop_test(tc, sum_calc_error, 0, 100);
  tcase_add_loop_test(tc, sub_calc_error, 0, 100);
  tcase_add_loop_test(tc, mult_number, 0, 100);
  tcase_add_loop_test(tc, mult_matrix, 0, 100);
  tcase_add_loop_test(tc, mult_matrix_error, 0, 100);
  tcase_add_loop_test(tc, transpose, 0, 100);
  tcase_add_test(tc, determinant);
  tcase_add_test(tc, inverse);
  tcase_add_test(tc, complements);
  suite_add_tcase(s, tc);
  return s;
}
