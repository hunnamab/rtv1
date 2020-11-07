#include "matrix.h"

void    matr_mul_by_scalar(double **matrix, int numRows, int numCols, int scalar)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < numRows)
	{
		while (j < numCols)
		{
			matrix[i][j] *= scalar;
			j++;
		}
		j = 0;
		i++;
	}
}
