#include "matrix.h"

double  **matr_transpose(double **matr)
{
	int newRows;
	int newCols;
	double  **trans_matrix;
	int i;
	int j;

	newRows = 4;
	newCols = 4;
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
