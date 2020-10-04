#include "matrix.h"

void    matr_add_matr(float **matrix1, float **matrix2, int numRows, int numCols)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < numRows)
    {
        while (j < numCols)
        {
            matrix1[i][j] += matrix2[i][j];
            j++;
        }
        j = 0;
        i++;
    }
}