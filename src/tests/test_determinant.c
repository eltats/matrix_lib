#include "tests.h"

START_TEST(determinant) {
  const int size = 3;
  double result = 0;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 3;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 1;
  A.matrix[2][0] = 9;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = 1;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq_tol(result, -32, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST
