#include "matrix.h"

double  get_sum(double **matrix1, double **matrix2, int n, int i, int j)
{
    double  sum;
    int k;

    k = 0;
    sum = 0;
    while (k < n)
    {
        sum += matrix1[i][k] * matrix2[k][j];
        k++;
    }
    return(sum);
}

void    matr_mul_void(double *matrix1, double **matrix2)
{
    int i;
    int j;
    double buf;
    double m_buf[4];

    i = -1;
    while (i++ < 4)
        m_buf[i] = matrix1[i];
    i = 0;
    j = 0;
    buf = 0;
    while (i < 4)
    {
        while (j < 4)
        {   
            buf += matrix2[i][j] * m_buf[j];
            j++;
        }
        matrix1[i] = buf;
        buf = 0;
        j = 0;
        i++;
    }
}

double    **matr_mul(double **matrix1, double **matrix2, int numRows1, int numCols1, int numRows2, int numCols2)
{
    double **result;
    int resultRows;
    int resultCols;
    int i;
    int j;

    i = 0;
    j = 0;
    if (numCols1 != numRows2)
    {
        printf("number of cols 1 != number of rows 2");
        return(NULL);
    }
    resultRows = numRows1;
    resultCols = numCols2; 
    result = create_matrix(resultRows, resultCols);
    while (i < resultRows)
    {
        while (j < resultCols)
        {
            result[i][j] = get_sum(matrix1, matrix2, numCols1, i, j);
            j++;
        }
        j = 0;
        i++;
    }
    return(result);
}