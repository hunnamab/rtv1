#include "matrix.h"

int         *matr_to_line(float **matrix, int numRows, int numCols)
{
    int *line;
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    line = (int *)malloc(sizeof(int) * numRows * numCols);
    while(i < numRows)
    {
        while (j < numCols)
        {
            line[k] = matrix[i][j];
            j++;
            k++;
        }
        j = 0;
        i++;
    }
    return(line);
}