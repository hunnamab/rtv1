#include "matrix.h"

void    matr_resize(double ***matrix, int numRows, int numCols, int newRows, int newCols)
{
    double **resized_matrix;

    resized_matrix = create_matrix(newRows, newCols);
    matr_copy(matrix[0], resized_matrix, numRows, numCols);
    matr_free(matrix[0], numRows);
    matrix[0] = resized_matrix;
}