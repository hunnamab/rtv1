#include "matrix.h"

void     matr_swap_cols(float **matr, int numRows, int numCols, int col1, int col2)
{
    float *buf;
    int i;

    i = 0;
    buf = (float *)malloc(sizeof(float) * numRows);
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