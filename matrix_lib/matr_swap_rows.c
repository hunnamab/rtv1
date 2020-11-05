#include "matrix.h"

void     matr_swap_rows(double **matr, int numRows, int numCols, int row1, int row2)
{
    double *buf;
    int i;

    i = 0;
    buf = (double *)malloc(sizeof(double) * numCols);
    while (i < numCols)
    {
        buf[i] = matr[row2][i];
        matr[row2][i] = matr[row1][i];
        i++;
    }
    i = 0;
    while(i < numCols)
    {
        matr[row1][i] = buf[i];
        i++;
    }
    free(buf);
}