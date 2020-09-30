#include "rtv1.h"

t_object *new_cone(t_point position, float specular, t_color color)
{
    t_cone *new_cone;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_cone = malloc(sizeof(t_triangle));
    new_cone->position = position;
    new_object->specular = specular;
    new_object->color = color;
    new_object->data = (void *)new_cone;
    new_object->tag = "cone";
    new_object->intersect = &intersect_ray_cone;
    return(new_object);
}

int intersect_ray_cone(t_ray *r, t_object *object, t_color *reflected_color, t_light **light)
{
    float a;
    float b;
    float c;
    float discr;
    float sqrt_discr;
    float t0;
    float t1;
    t_point dist;
    t_point buf;
    t_cone *cone;
    t_point intersection_point;
    t_point normal;

    cone = (t_cone *)object->data;
    a = r->dir.x * r->dir.x + r->dir.z * r->dir.z - r->dir.y * r->dir.y;
    dist = vector_sub(&r->start, &cone->position);
    b = 2 * dist.x * r->dir.x + 2 * dist.z * r->dir.z - 2 * dist.y * r->dir.y;
    c = dist.x * dist.x + dist.z * dist.z - dist.y * dist.y;
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
        // normal
        normalize_vector(&normal);
        *(t_color *)reflected_color = reflection_color(&intersection_point, &normal, &r->dir, object, light);
        return (1);
    }
    return (0);
}
