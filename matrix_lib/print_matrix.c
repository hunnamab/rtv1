#include "matrix.h"

void    print_matrix(double **matrix, int numRows, int numCols)
{
	int j = 0;
	int i = 0;
	while (i < numRows)
	{
		while(j < numCols)
		{
			printf("%f   ", matrix[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}
