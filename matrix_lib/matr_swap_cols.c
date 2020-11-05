#include "matrix.h"

void     matr_swap_cols(double **matr, int numRows, int numCols, int col1, int col2)
{
    double *buf;
    int i;

    i = 0;
    buf = (double *)malloc(sizeof(double) * numRows);
    while (i < numRows)
    {
        buf[i] = matr[i][col2];
        matr[i][col2] = matr[i][col1];
        i++;
    }
    i = 0;
    while(i < numRows)
    {
        matr[i][col1] = buf[i];
        i++;
    }
    free(buf);
}