#include "matrix.h"

float  **matr_transpose(float **matr, int numRows, int numCols)
{
    int newRows;
    int newCols;
    float  **trans_matrix;
    int i;
    int j;

    newRows = numCols;
    newCols = numRows;
    trans_matrix = create_matrix(newRows, newCols);
    i = 0;
    j = 0;
    while (i < newRows)
    {
        while(j < newCols)
        {
            trans_matrix[i][j] = matr[j][i];
            j++;
        }
        j = 0;
        i++;
    }
    return(trans_matrix);
}