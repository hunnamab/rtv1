#ifndef MATRIX_H
# define MATRIX_H
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


double      **create_matrix(int numRows, int numCols);
void        print_matrix(double **matrix, int numRows, int numCols);
double      **matr_mul(double **matrix1, double **matrix2);
void        matr_mul_by_scalar(double **matrix, int numRows, int numCols, int scalar);
void        matr_div_by_scalar(double **matrix, int numRows, int numCols, int scalar);
void        matr_add_scalar(double **matrix, int numRows, int numCols, int scalar);
void        matr_sub_scalar(double **matrix, int numRows, int numCols, int scalar);
void        matr_add_matr(double **matrix1, double **matrix2, int numRows, int numCols);
void        matr_sub_matr(double **matrix1, double **matrix2, int numRows, int numCols);
double      matr_trace(double **matrix, int numRows, int numCols);
double      **matr_transpose(double **matr);
void        matr_resize(double ***matrix, int numRows, int numCols, int newRows, int newCols);
void        matr_copy(double **srcMatrix, double **dstMatrix, int numRows, int numCols);
void        matr_free(double **matrix, int numRows);
int         *matr_to_line(double **matrix, int numRows, int numCols);
void        matrix_identity(double **matrix, int numrows);
void        matr_mul_void(double *matrix1, double **matrix2);

#endif