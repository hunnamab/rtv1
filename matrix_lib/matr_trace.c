#include "matrix.h"

float      matr_trace(float **matrix, int numRows, int numCols)
{
    int i;
    float result;

    i = 0;
    result = 0;
    if (numCols != numRows)
    {
        printf("matrix isn't square");
        return(-1);
    }
    while (i < numRows)
    {
        result += matrix[i][i];
        i++;
    }
    return (result);
}