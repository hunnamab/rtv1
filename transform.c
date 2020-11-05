#include "rtv1.h"

double   *get_three_doubles(double x, double y, double z)
{
    double   *angles;

    angles = malloc(sizeof(double) * 3);
    angles[0] = x;
    angles[1] = y;
    angles[2] = z;
    return(angles);
}

double **get_translate_matrix(double *move)
{
    double **t_matrix;

    t_matrix = create_matrix(4, 4);
    matrix_identity(t_matrix, 4);
    t_matrix[0][3] = move[0];
    t_matrix[1][3] = move[1];
    t_matrix[2][3] = move[2];
    return(t_matrix);
}

double **get_scale_matrix(double *scale)
{
    double **s_matrix;
    
    s_matrix = create_matrix(4, 4);
    s_matrix[0][0] = scale[0];
    s_matrix[1][1] = scale[1];
    s_matrix[2][2] = scale[2];
    s_matrix[3][3] = 1;
    return(s_matrix);
}

double **rotate_x(double x)
{
    double **matrix;

    matrix = create_matrix(4,4);
    matrix[0][0] = 1;
    matrix[0][2] = 0;
    matrix[1][1] = cosf(x);
    matrix[1][2] = -sinf(x);
    matrix[2][1] = sinf(x);
    matrix[2][2] = cosf(x);
    matrix[3][3] = 1;
    return(matrix);
}

double **rotate_z(double z)
{
    double **matrix;

    matrix = create_matrix(4,4);
    matrix[0][0] = cosf(z);
    matrix[0][1] = -sinf(z);
    matrix[1][0] = sinf(z);
    matrix[1][1] = cosf(z);
    matrix[2][2] = 1;
    matrix[3][3] = 1;
    return(matrix);
}

double **rotate_y(double y)
{
    double **matrix;

    matrix = create_matrix(4,4);
    matrix[0][0] = cosf(y);
    matrix[0][2] = sinf(y);
    matrix[1][1] = 1;
    matrix[2][0] = -sinf(y);
    matrix[2][2] = cosf(y);
    matrix[3][3] = 1;
    return(matrix);
}

double **get_rotation_matrix_euler(double *angle)
{
    double **rotation_matrix;
    double x;
    double y;
    double z;

    x = angle[0];
    y = angle[1];
    z = angle[2];
    rotation_matrix = create_matrix(4,4);
    rotation_matrix[0][0] = cosf(x) * cosf(z) - cosf(y) * sinf(x) * sinf(z);
    rotation_matrix[1][0] = cosf(y) * cosf(z) * sinf(x) + cosf(x) * sinf(z);
    rotation_matrix[2][0] = sinf(x) * sinf(y);
    rotation_matrix[0][1] = -cosf(z) * sinf(x) - cosf(x) * cosf(y) * sinf(z);
    rotation_matrix[1][1] = cosf(x) * cosf(y) * cosf(z) - sinf(x) * sinf(z);
    rotation_matrix[2][1] = cosf(x) * sinf(y);
    rotation_matrix[0][2] = sinf(y) * sinf(z);
    rotation_matrix[1][2] = -cosf(z) * sinf(y);
    rotation_matrix[2][2] = cosf(y);
    rotation_matrix[3][3] = 1;
    return(rotation_matrix);
}

double **get_rotation_matrix(double *angle)
{
    double **rotation_matrix;
    double **rotation_buf;
    double **rotation_buf_second;

    rotation_buf = rotate_z(angle[2]);
    rotation_buf_second = rotate_y(angle[1]);
    rotation_matrix = matr_mul(rotation_buf, rotation_buf_second, 4, 4, 4, 4);
    matr_free(rotation_buf, 4);
    matr_free(rotation_buf_second, 4);
    rotation_buf = rotate_x(angle[0]);
    rotation_buf_second = matr_mul(rotation_matrix, rotation_buf, 4, 4, 4, 4);
    matr_free(rotation_buf, 4);
    matr_free(rotation_matrix, 4);
    return(rotation_buf_second);
}

void    transform(t_point *point, double **matrix, int point_nmb)
{
    int i;
    double coord_matrix[4];

    i = 0;
    while(i < point_nmb)
    {
        coord_matrix[0] = point[i].x;
        coord_matrix[1] = point[i].y;
        coord_matrix[2] = point[i].z;
        coord_matrix[3] = 1;
        matr_mul_void(coord_matrix, matrix);
        point[i].x = coord_matrix[0];
        point[i].y = coord_matrix[1];
        point[i].z = coord_matrix[2];
        i++;
    }
}

double     **get_transform_matrix(double *angle, double *move, double *scale)
{
    double **t_matrix; 
    double **s_matrix;
    double **rotation_matrix;
    double **result_matrix;
    double **result;

    t_matrix = get_translate_matrix(move);
    s_matrix = get_scale_matrix(scale);
    rotation_matrix = get_rotation_matrix(angle);
    result_matrix = matr_mul(s_matrix, rotation_matrix, 4, 4, 4, 4);
    matr_free(rotation_matrix, 4);
    matr_free(s_matrix, 4);
    result = matr_mul(t_matrix, result_matrix, 4, 4, 4, 4);
    matr_free(result_matrix, 4);
    matr_free(t_matrix, 4);
    return (result);
}