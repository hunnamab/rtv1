#include "rtv1.h"

float   *get_angles(float x, float y, float z)
{
    float   *angles;

    angles = malloc(sizeof(float) * 3);
    angles[0] = x;
    angles[1] = y;
    angles[2] = z;
    return(angles);
}

float **get_translate_matrix(float *move)
{
    float **t_matrix;

    t_matrix = create_matrix(4, 4);
    matrix_identity(t_matrix, 4);
    t_matrix[0][3] = move[0];
    t_matrix[1][3] = move[1];
    t_matrix[2][3] = move[2];
    return(t_matrix);
}

float **get_scale_matrix(float *scale)
{
    float **s_matrix;
    
    s_matrix = create_matrix(4, 4);
    s_matrix[0][0] = scale[0];
    s_matrix[1][1] = scale[1];
    s_matrix[2][2] = scale[2];
    s_matrix[3][3] = 1;
    return(s_matrix);
}

float **get_rotation_matrix(float *angle)
{
    float **rotation_matrix;
    float x;
    float y;
    float z;

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
/* пока что будет работать на одну точку/вектор, в дальнейшем можно принимать структуру, с массивом точек и количеством этих точек и другой доп.инфой */
void     translate(t_point *points, float *angle, float *move, float *scale)
{
    float **t_matrix; //translation matrix
    float **s_matrix;
    float **rotation_matrix;
    float **result_matrix;
    float **coord_matrix;
    float **result;
    float **final;

    coord_matrix = create_matrix(4, 1);
    coord_matrix[0][0] = points[0].x;
    coord_matrix[1][0] = points[0].y;
    coord_matrix[2][0] = points[0].z;
    coord_matrix[3][0] = 1;
    t_matrix = get_translate_matrix(move);
    s_matrix = get_scale_matrix(scale);
    rotation_matrix = get_rotation_matrix(angle);
    result_matrix = matr_mul(s_matrix, rotation_matrix, 4, 4, 4, 4);
    matr_free(rotation_matrix, 4);
    matr_free(s_matrix, 4);
    result = matr_mul(t_matrix, result_matrix, 4, 4, 4, 4);
    matr_free(result_matrix, 4);
    matr_free(t_matrix, 4);
    final = matr_mul(result, coord_matrix, 4, 4, 4, 1);
    points[0].x = final[0][0];
    points[0].y = final[1][0];
    points[0].z = final[2][0];
}