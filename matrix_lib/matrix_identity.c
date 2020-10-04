#include "matrix.h"

void    matrix_identity(float **matrix, int numrows)
{
    int i;

    i = 0;
    while(i < numrows)
    {
        matrix[i][i] = 1;
        i++;
    }
}