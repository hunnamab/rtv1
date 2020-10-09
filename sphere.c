#include "rtv1.h"

t_object *new_sphere(t_point center, float radius, float specular, t_color color)
{
    t_sphere *new_sphere;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_sphere = malloc(sizeof(t_sphere));
    new_sphere->center = center;
    new_sphere->radius = radius;
    new_object->specular = specular;
    new_object->color = color;
    new_object->data = (void *)new_sphere;
    new_object->tag = "sphere";
    new_object->intersect = &intersect_ray_sphere;
    return(new_object);
}

int intersect_ray_sphere(t_ray *r, t_object *object, t_point *normal, float *t)
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
    t_point buf;
    t_sphere *s;
 
    s = (t_sphere *)object->data;
    a = vector_dot(&r->dir, &r->dir);
    dist = vector_sub(&r->start, &s->center);
    b = 2 * vector_dot(&dist, &r->dir);
    c = vector_dot(&dist, &dist) - (s->radius * s->radius);
    discr = b * b - 4 * a * c;
    if (discr < 0)
        return (0);
    else
    {
        sqrt_discr = sqrt(discr);
        t0 = (-b + sqrt_discr) / (2 * a);
        t1 = (-b - sqrt_discr) / (2 * a);
        if (t0 > t1)
            buf = vector_scale(t1, &r->dir);
        else
            buf = vector_scale(t0, &r->dir);
        intersection_point = vector_add(&r->start, &buf);
        *t = t1 < t0 ? t1 : t0;
        normal[0] = vector_sub(&intersection_point, &s->center);
        normal[0] = vector_div_by_scalar(normal, vector_length(normal));
        return(1);
    }
    return (0);
}
