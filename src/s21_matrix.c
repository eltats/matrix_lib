#include "s21_matrix.h"

void cofactor(double **m, double **tmp, int skip_row, int skip_col, int size) {
  for (int i = 0, row = 0; row < size; row++) {
    for (int j = 0, col = 0; col < size; col++) {
      if (row != skip_row && col != skip_col) {
        tmp[i][j] = m[row][col];
        j++;
        if (j == size - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}

int check_matrixes(matrix_t *A, matrix_t *B) {
  int code = SUCCESS;
  if (A->columns <= 0 || A->rows <= 0 || B->rows <= 0 || B->columns <= 0)
    code = FAILURE;
  return code;
}

int check_matrix(matrix_t *A) {
  int code = SUCCESS;
  if (A->columns <= 0 || A->rows <= 0) code = FAILURE;
  return code;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 && columns <= 0) return INCORRECT_MATRIX;
  if (!(result->matrix = (double **)calloc(rows, sizeof(double *))))
    return ALLOC_FAIL;
  result->rows = rows;
  result->columns = columns;
  for (int i = 0; i < rows; i++) {
    if (!(result->matrix[i] = (double *)calloc(columns, sizeof(double)))) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[i]);
      }
      free(result->matrix);
      return ALLOC_FAIL;
    }
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = 0;
    }
  }
  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int code = SUCCESS;
  if (check_matrixes(A, B) == FAILURE) code = FAILURE;
  if (code == SUCCESS) {
    if (A->columns != B->columns || A->rows != B->rows) code = FAILURE;
    for (int i = 0; i < A->rows && code == SUCCESS; i++) {
      for (int j = 0; j < A->columns && code == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) code = FAILURE;
      }
    }
  }
  return code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrixes(A, B) == FAILURE) return INCORRECT_MATRIX;
  if (A->rows != B->rows || A->columns != B->columns) return CALCULATION_ERROR;
  if (s21_create_matrix(A->rows, A->columns, result) != OK) return ALLOC_FAIL;
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrixes(A, B) == FAILURE) return INCORRECT_MATRIX;
  if (A->rows != B->rows || A->columns != B->columns) return CALCULATION_ERROR;
  if (s21_create_matrix(A->rows, A->columns, result) != OK) return ALLOC_FAIL;
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (check_matrix(A) == FAILURE) return INCORRECT_MATRIX;
  if (s21_create_matrix(A->rows, A->columns, result) != OK) return ALLOC_FAIL;
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (check_matrixes(A, B) == FAILURE) return INCORRECT_MATRIX;
  if (A->columns != B->rows || B->columns != A->rows) return CALCULATION_ERROR;
  if (s21_create_matrix(A->rows, A->rows, result) != OK) return ALLOC_FAIL;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++)
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
    }
  }
  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) == FAILURE) return INCORRECT_MATRIX;
  if (s21_create_matrix(A->columns, A->rows, result) != OK) return ALLOC_FAIL;
  for (int i = 0; i < A->columns; i++) {
    for (int j = 0; j < A->rows; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }
  return OK;
}

double calc_det(matrix_t *A, int size) {
  if (size == 1) return A->matrix[0][0];
  double result = 0;
  matrix_t tmp = {0};
  if (s21_create_matrix(size, size, &tmp) != OK) return ALLOC_FAIL;
  int sign = 1;
  for (int i = 0; i < size; i++) {
    cofactor(A->matrix, tmp.matrix, 0, i, size);
    result += sign * A->matrix[0][i] * calc_det(&tmp, size - 1);
    sign = -sign;
  }
  s21_remove_matrix(&tmp);
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  if (check_matrix(A) == FAILURE) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  if (A->rows == 1)
    *result = A->matrix[0][0];
  else
    *result = calc_det(A, A->rows);
  return OK;
}

void form_complements(matrix_t *A, matrix_t *result) {
  if (A->rows == 1) {
    result->matrix[0][0] = 1;
    return;
  }
  matrix_t tmp = {0};
  int sign = 0;

  if (s21_create_matrix(A->rows, A->rows, &tmp) != OK) return;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      cofactor(A->matrix, tmp.matrix, i, j, A->rows);
      sign = ((i + j) % 2 == 0) ? 1 : -1;
      result->matrix[i][j] = sign * calc_det(&tmp, A->rows - 1);
    }
  }
  s21_remove_matrix(&tmp);
}
// void form_inversecomplements(matrix_t *A, matrix_t *result) {
//   if (A->rows == 1) {
//     result->matrix[0][0] = 1;
//     return;
//   }
//   matrix_t tmp = {};
//   int sign = 0;

//   if (s21_create_matrix(A->rows, A->columns, &tmp) != OK) return;
//   for (int i = 0; i < A->rows; i++) {
//     for (int j = 0; j < A->columns; j++) {
//       cofactor(A->matrix, tmp.matrix, i, j, A->rows);
//       sign = ((i + j) % 2 == 0) ? 1 : -1;
//       result->matrix[j][i] = sign * calc_det(&tmp, A->rows - 1);
//     }
//   }
//   s21_remove_matrix(&tmp);
// }
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) == FAILURE) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  if (s21_create_matrix(A->columns, A->rows, result) != OK) return ALLOC_FAIL;
  form_complements(A, result);
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (check_matrix(A) == FAILURE) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;

  double det = 0;
  int error = s21_determinant(A, &det);
  if (fabs(det) < 1e-6 || error != OK) return CALCULATION_ERROR;

  matrix_t a = {0}, trans = {0};

  if (s21_calc_complements(A, &a) != OK) return ALLOC_FAIL;
  if (s21_transpose(&a, &trans) || s21_create_matrix(A->rows, A->rows, result))
    return ALLOC_FAIL;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->rows; j++) {
      result->matrix[i][j] = trans.matrix[i][j] / det;
    }
  }
  s21_remove_matrix(&a);
  s21_remove_matrix(&trans);
  return OK;
}
