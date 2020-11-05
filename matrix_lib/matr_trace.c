#include "matrix.h"

double      matr_trace(double **matrix, int numRows, int numCols)
{
    int i;
    double result;

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