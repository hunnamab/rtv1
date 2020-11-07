#include "matrix.h"

double **create_matrix(int numRows, int numCols)
{
	int j = 0;
	int i = 0;
	double **matrix;

	matrix = (double **)malloc(sizeof(double *) * numRows);
	while(i < numRows)
	{
		matrix[i] = (double *)malloc(sizeof(double) * numCols);
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
