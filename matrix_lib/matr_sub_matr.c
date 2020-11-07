#include "matrix.h"

void    matr_sub_matr(double **matrix1, double **matrix2, int numRows, int numCols)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < numRows)
	{
		while (j < numCols)
		{
			matrix1[i][j] -= matrix2[i][j];
			j++;
		}
		j = 0;
		i++;
	}
}
