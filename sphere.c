#include "rtv1.h"

t_sphere *new_sphere(t_point center, int16_t radius)
{
    t_sphere *new_sphere;

    new_sphere = malloc(sizeof(t_sphere));
    new_sphere->center = center;
    new_sphere->radius = radius;
    new_sphere->color.red = 255;
    new_sphere->color.green = 0;
    new_sphere->color.blue = 0;
    new_sphere->color.alpha = 255;
    return(new_sphere);
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
    float dot = vector_dot(vector, vector);\
    float result = sqrt(dot);
    return(result);
}

int intersect_ray_sphere(t_ray *r, t_sphere *s)
{
    float a;
    float b;
    float c;
    float discr;
    float sqrt_discr;
    float t0;
    float t1;
    t_point dist;
    t_point intersection_point;
    t_point normal;
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
    if (discr <= 0)
        return (0);
    else
    {
        sqrt_discr = sqrt(discr);
        t0 = (-b + sqrt_discr) / (2 * a);
        t1 = (-b - sqrt_discr) / (2 * a);
        t_point buf;
        if (t0 > t1)
        {
            buf = vector_scale(t1, &r->dir);
            intersection_point = vector_add(&r->start, &buf);
        }
        else
        {
            buf = vector_scale(t0, &r->dir);
            intersection_point = vector_add(&r->start, &buf);
        }
        normal = vector_sub(&intersection_point, &s->center);
        normal = vector_div_by_scalar(&normal, vector_length(&normal));
        reflection_color(&intersection_point, &normal, &s->color);
        return(1);
    }
    return (0);
}
