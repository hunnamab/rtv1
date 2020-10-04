#include "matrix.h"

float **create_matrix(int numRows, int numCols)
{
    int j = 0;
    int i = 0;
    float **matrix;

    matrix = (float **)malloc(sizeof(float *) * numRows);
    while(i < numRows)
    {
        matrix[i] = (float *)malloc(sizeof(float) * numCols);
        while (j < numCols)
        {
            matrix[i][j] = 0.0;
            j++;
        }
        j = 0;
        i++;
    }
    return(matrix);
}