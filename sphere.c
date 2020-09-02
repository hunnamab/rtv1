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

int intersect_ray_sphere(t_ray *r, t_sphere *s, float *t)
{
    float a;
    float b;
    float c;
    float discr;
    float sqrt_discr;
    float t0;
    float t1;
    t_point dist;
    
    /* a = d.d, the vector dot product of the direction */
    a = vector_dot(&r->dir, &r->dir);

    /* We need a vector representing the distance between the start of 
    * the ray and the position of the circle.
    * This is the term (p0 - c)
    */
    dist = vector_sub(&r->start, &s->center);

    /* b = 2d.(p0 - c) */
    b = 2 * vector_dot(&r->dir, &dist);

    /* c = (p0 - c).(p0 - c) - r^2 */
    c = vector_dot(&dist, &dist) - (s->radius * s->radius);

    /* Solving the discriminant */
    discr = b * b - 4 * a * c;
    
    /* If the discriminant is negative, there are no real roots.
    * Return false in that case as the ray misses the sphere.
    * Return true in all other cases (can be one or two intersections)
    */
    if (discr < 0)
        return (0);
    else
    {
        /*sqrt_discr = sqrt(discr);
        t0 = (-b + sqrt_discr) / 2;
        t1 = (-b - sqrt_discr) / 2;
        if (t0 > t1)
            t0 = t1;
        if (t0 > 0.001f && t0 < *t)
        {
            *t = t0;
            return (1);
        }
        else
            return (0);*/
            return (1);
    }
    return (0);
}
