#include "rtv1.h"

t_point vector_add(t_point *v1, t_point *v2)
{
    t_point res;

    res.x = v1->x + v2->x;
    res.y = v1->y + v2->y;
    res.z = v1->z + v2->z;
    return (res);
}

t_point vector_scale(float c, t_point *v)
{
    t_point res;

    res.x = v->x * c;
    res.y = v->y * c;
    res.z = v->z * c;
    return (res);
}

t_point vector_sub(t_point *v1, t_point *v2)
{
    t_point res;

    res.x = v1->x - v2->x;
    res.y = v1->y - v2->y;
    res.z = v1->z - v2->z;
    return (res);
}

float vector_dot(t_point *v1, t_point *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_point     vector_sub_by_scalar(t_point *vector, float scalar)
{
    t_point result;

    result.x = vector->x + scalar;
    result.y = vector->y + scalar;
    result.z = vector->z + scalar;
    return(result);
}

t_point     vector_div_by_scalar(t_point *vector, float scalar)
{
    t_point result;

    result.x = vector->x / scalar;
    result.y = vector->y / scalar;
    result.z = vector->z / scalar;
    return(result);
}

float   vector_length(t_point *vector)
{
    float dot = vector_dot(vector, vector);
    return (sqrt(dot));
}

t_point  vector_cross(t_point *v1, t_point *v2)
{
    t_point result;

    result.x = v1->y * v2->z - v1->z * v2->y;
    result.y = v1->z * v2->x - v1->x * v2->z;
    result.z = v1->x * v2->y - v1->y * v2->x;

    return(result);
}
