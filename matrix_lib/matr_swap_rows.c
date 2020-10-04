#include "matrix.h"

void     matr_swap_rows(float **matr, int numRows, int numCols, int row1, int row2)
{
    float *buf;
    int i;

    i = 0;
    buf = (float *)malloc(sizeof(float) * numCols);
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