#include "tests.h"

START_TEST(transpose) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1, value = 0;
  matrix_t A, expected, result;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &expected);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      value = rand() % 100 + 1;
      A.matrix[i][j] = value;
      expected.matrix[j][i] = value;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST
