#include "tests.h"

START_TEST(sum) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1, value = 0,
      value2 = 0;
  matrix_t A, B, expected, result;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &expected);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      value = rand() % 100;
      value2 = rand() % 100;
      A.matrix[i][j] = value;
      B.matrix[i][j] = value2;
      expected.matrix[i][j] = value + value2;
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_calc_error) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1;
  int rows2 = rand() % 100 + 1, columns2 = rand() % 100 + 1;
  matrix_t A, B, result;
  if (rows == rows2) rows++;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows2, columns2, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1, value = 0,
      value2 = 0;
  matrix_t A, B, expected, result;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &expected);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      value = rand() % 100;
      value2 = rand() % 100;
      A.matrix[i][j] = value;
      B.matrix[i][j] = value2;
      expected.matrix[i][j] = value - value2;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_calc_error) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1;
  int rows2 = rand() % 100 + 1, columns2 = rand() % 100 + 1;
  matrix_t A, B, result;
  if (rows == rows2) rows++;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows2, columns2, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
