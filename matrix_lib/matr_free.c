#include "matrix.h"

void    matr_free(double **matrix, int numRows)
{
	int i;

	i = 0;
	while (i < numRows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
