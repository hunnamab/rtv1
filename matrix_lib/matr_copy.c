#include "matrix.h"

void    matr_copy(float **srcMatrix, float **dstMatrix, int numRows, int numCols)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < numRows)
    {
        while (j < numCols)
        {
            dstMatrix[i][j] = srcMatrix[i][j];
            j++;
        }
        j = 0;
        i++;
    }
}