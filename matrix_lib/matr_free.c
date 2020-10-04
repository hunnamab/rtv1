#include "matrix.h"

void    matr_free(float **matrix, int numRows)
{
    int i;

    i = 0;
    while (i < numRows)
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}