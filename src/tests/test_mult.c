#include "tests.h"

START_TEST(mult_number) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1, value = 0;
  matrix_t A, expected, result;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &expected);
  double value2 = rand() % 100;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      value = rand() % 100;
      A.matrix[i][j] = value;
      expected.matrix[i][j] = value * value2;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, value2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1;
  matrix_t A, B, result, expected;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &B);
  s21_create_matrix(A.rows, B.columns, &result);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) A.matrix[i][j] = rand() % 100 + 1;

  for (int i = 0; i < columns; i++)
    for (int j = 0; j < rows; j++) B.matrix[i][j] = rand() % 100 + 1;

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      result.matrix[i][j] = 0;
      for (int k = 0; k < A.columns; k++)
        result.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &expected), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_error) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1;
  int rows2 = rand() % 100 + 1, columns2 = rand() % 100 + 1;
  if (rows == columns2) rows++;
  if (rows2 == columns) rows2++;

  matrix_t A, B, result;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows2, columns2, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
