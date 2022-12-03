#include "tests.h"

START_TEST(create_and_free) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1;
  matrix_t test;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &test), OK);
  ck_assert_int_eq(test.columns, columns);
  ck_assert_int_eq(test.rows, rows);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      test.matrix[i][j] = 0;
      ck_assert_double_eq_tol(test.matrix[i][j], 0, 1e-6);
    }
  }
  s21_remove_matrix(&test);
}
END_TEST

START_TEST(create_wrong) {
  int rows = (rand() % 100) * -1, columns = (rand() % 100) * -1;
  matrix_t test;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &test), INCORRECT_MATRIX);
}
END_TEST
