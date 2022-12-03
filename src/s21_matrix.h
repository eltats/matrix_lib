#ifndef SRC_S21_MATRIX_H__
#define SRC_S21_MATRIX_H__

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define ALLOC_FAIL 3
#define EPS 1e-7

#include <math.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/*
The transpose of matrix A is in switching its rows with its columns with their
numbers retained
*/
int s21_transpose(matrix_t *A, matrix_t *result);

/*
Minor M(i,j) is a (n-1)-order determinant obtained by deleting out the i-th row
and the j-th column from the matrix A.
*/
int s21_calc_complements(matrix_t *A, matrix_t *result);

/*
The determinant is a number that is associated to each square matrix and
calculated from the elements using special formulas.
*/
int s21_determinant(matrix_t *A, double *result);

/*
A matrix A to the power of -1 is called the inverse of a square matrix A if the
product of these matrices equals the identity matrix.
*/
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif
