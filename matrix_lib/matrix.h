#ifndef MATRIX_H
# define MATRIX_H
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


float      **create_matrix(int numRows, int numCols);
void        matr_swap_rows(float **matr, int numRows, int numCols, int row1, int row2);
void        matr_swap_cols(float **matr, int numRows, int numCols, int col1, int col2);
void        print_matrix(float **matrix, int numRows, int numCols);
float      **matr_mul(float **matrix1, float **matrix2, int numRows1, int numCols1, int numRows2, int numCols2);
void        matr_mul_by_scalar(float **matrix, int numRows, int numCols, int scalar);
void        matr_div_by_scalar(float **matrix, int numRows, int numCols, int scalar);
void        matr_add_scalar(float **matrix, int numRows, int numCols, int scalar);
void        matr_sub_scalar(float **matrix, int numRows, int numCols, int scalar);
void        matr_add_matr(float **matrix1, float **matrix2, int numRows, int numCols);
void        matr_sub_matr(float **matrix1, float **matrix2, int numRows, int numCols);
float      matr_trace(float **matrix, int numRows, int numCols);
float      **matr_transpose(float **matr, int numRows, int numCols);
void        matr_resize(float ***matrix, int numRows, int numCols, int newRows, int newCols);
void        matr_copy(float **srcMatrix, float **dstMatrix, int numRows, int numCols);
void        matr_free(float **matrix, int numRows);
int         *matr_to_line(float **matrix, int numRows, int numCols);
void        matrix_identity(float **matrix, int numrows);
void        matr_mul_void(float *matrix1, float **matrix2);

#endif