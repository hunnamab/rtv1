#include <stdio.h>
#include <math.h>
#define HEI 600
#define WID 800

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
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

t_point vector_scale(double c, t_point *v)
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

double vector_dot(t_point *v1, t_point *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}


t_point     vector_sub_by_scalar(t_point *vector, double scalar)
{
    t_point result;

    result.x = vector->x + scalar;
    result.y = vector->y + scalar;
    result.z = vector->z + scalar;
    return(result);
}

t_point     vector_div_by_scalar(t_point *vector, double scalar)
{
    t_point result;

    result.x = vector->x / scalar;
    result.y = vector->y / scalar;
    result.z = vector->z / scalar;
    return(result);
}

double   vector_length(t_point *vector)
{
    double dot = vector_dot(vector, vector);
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

t_point     get_point(double x, double y, double z)
{
    t_point result;

    result.x = x;
    result.y = y;
    result.z = z;
    return (result);
}
double   choose_t(double t0, double t1)
{
    double result;

    result = 0;
    if ((t1 < t0 && t1 > 0) || (t0 < 0 && t1 >= 0))
        result = t1;
    if ((t0 < t1 && t0 > 0) || (t1 < 0 && t0 >= 0))
        result = t0;
    if(t0 == t1 && t0 > 0)
        result = t0;
    printf("t0 == %f  t0 == %f\n",t0, t1);
    return(result);
}
double intersect(t_ray *r)
{
    double a;
    double b;
    double c;
    double discr;
    t_point dist;
    t_point center;

    center = get_point(0,0,0);
    a = vector_dot(&r->dir, &r->dir);
    dist = vector_sub(&r->start, &center);
    b = 2 * vector_dot(&dist, &r->dir);
    c = vector_dot(&dist, &dist) - (300 * 300);
    discr = b * b - 4 * a * c;
    if (discr >= 0)
    {
        discr = sqrt(discr);
        return (choose_t((-b + discr) / (2 * a), (-b - discr) / (2 * a)));
    }
    return (0);
}
int main()
{
    char *test;
    t_ray r;

    r.start = get_point(123.494791, -62.362565, 266.195317);
    r.dir = get_point(-123.494791, 62.362565, -267.195317);
    printf("result t == %f\n", intersect(&r));
    return(0);
}