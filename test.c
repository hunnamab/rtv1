#include <stdio.h>
#include <math.h>
#define HEI 600
#define WID 800

typedef struct		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef struct		s_ray
{
	t_point			start;
	t_point			dir;
}					t_ray;

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

int main()
{
    t_ray r;
    float x;
    float y;
    t_point view_port_point;
    r.start.y = 0;
    r.start.z = 0;
    r.start.x = 0;
    y = 0;
    x = 0;
    view_port_point.z = 1;
    printf("HEI = %d WID = %d\n", HEI, WID);
    view_port_point.y = -(y - (float)HEI / 2) * (1 / ((float)HEI / 2));
    view_port_point.x = (x - (float)WID / 2) * (1 / ((float)WID / 2));
    printf("view_port_point.x == %f, view_port_point.y == %f\n", view_port_point.x, view_port_point.y);
    r.dir = vector_sub(&r.start, &view_port_point);
    printf("view_port_point.x == %f, view_port_point.y == %f\n", view_port_point.x, view_port_point.y);
    printf("dir.x == %f, dir.y == %f, dir.z = %f\n", r.dir.x, r.dir.y, r.dir.z);
    return(0);
}