#include "rtv1.h"

float   *get_three_floats(float x, float y, float z)
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
  /*   printf("t_matrix\n");
    print_matrix(t_matrix, 4, 4); */
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
   /*  printf("s_matrix\n");
    print_matrix(s_matrix, 4, 4); */
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
   /*  printf("r_matrix\n");
    print_matrix(rotation_matrix, 4, 4); */
    return(rotation_matrix);
}

/* умножает координаты точки на матрицу трансформации, для вызова нужен указатель на буфер coord_matrix для хранения изначальных координат точек
принимает массив точек, матрицу трансформации, буфер и количество точек */
void    transform(t_point *point, float **matrix, float *coord_matrix, int point_nmb)
{
    int i;

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

/* создает матрицу трансформации по указанным значениям вращения/перемещения/рескейла и возвращает ее */
float     **get_transform_matrix(float *angle, float *move, float *scale)
{
    float **t_matrix; //translation matrix
    float **s_matrix;
    float **rotation_matrix;
    float **result_matrix;
    float **result;

    t_matrix = get_translate_matrix(move);
    s_matrix = get_scale_matrix(scale);
    rotation_matrix = get_rotation_matrix(angle);
    result_matrix = matr_mul(s_matrix, rotation_matrix, 4, 4, 4, 4);
    matr_free(rotation_matrix, 4);
    matr_free(s_matrix, 4);
    result = matr_mul(t_matrix, result_matrix, 4, 4, 4, 4);
    matr_free(result_matrix, 4);
    matr_free(t_matrix, 4);
    /* printf("result_matrix\n");
    print_matrix(result, 4, 4); */
    return (result);
}