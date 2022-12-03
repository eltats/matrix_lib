#include "tests.h"

START_TEST(same_matrixes) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1, value = 0;
  matrix_t A, B;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      value = rand() % 100;
      A.matrix[i][j] = value;
      B.matrix[i][j] = value;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(not_equal) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1;
  int rows2 = rand() % 100 + 1, columns2 = rand() % 100 + 1;
  matrix_t A, B;
  if (rows == rows2) rows++;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows2, columns2, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(not_equal2) {
  int rows = rand() % 100 + 1, columns = rand() % 100 + 1, value = 0,
      value2 = 0;
  matrix_t A, B;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      value = rand() % 100;
      value2 = rand() % 100;
      if (value == value2) value++;
      A.matrix[i][j] = value;
      B.matrix[i][j] = value2;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST
