#include "rtv1.h"

t_object *new_cylinder(t_point position, float radius, float specular, t_color color)
{
    t_cylinder *new_cylinder;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_cylinder = malloc(sizeof(t_triangle));
    new_cylinder->position = position;
    new_cylinder->radius = radius;
    new_object->specular = specular;
    new_object->color = color;
    new_object->data = (void *)new_cylinder;
    new_object->tag = "cylinder";
    new_object->intersect = &intersect_ray_cylinder;
    return(new_object);
}

int intersect_ray_cylinder(t_ray *r, t_object *object, t_color *reflected_color, t_light **light)
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
    t_cylinder *cylinder;
    t_point intersection_point;
    t_point normal;

    cylinder = (t_cylinder *)object->data;
    a = r->dir.x * r->dir.x + r->dir.z * r->dir.z;
    dist.x = r->start.x - cylinder->position.x;
    dist.z = r->start.z - cylinder->position.z;
    b = r->dir.x * dist.x + r->dir.z * dist.z;
    c = dist.x * dist.x + dist.z * dist.z - cylinder->radius * cylinder->radius;
    discr = b * b - a * c;
    if (discr < 0)
        return (0);
    else
    {
        sqrt_discr = sqrt(discr);
        t0 = (-b + sqrt_discr) / (a);
        t1 = (-b - sqrt_discr) / (a);
        if (t0 > t1)
            buf = vector_scale(t1, &r->dir);
        else
            buf = vector_scale(t0, &r->dir);
        intersection_point = vector_add(&r->start, &buf);
        normal = vector_sub(&cylinder->position, &intersection_point);
        normal.y = 0;
        normalize_vector(&normal);
        if (vector_dot(&r->dir, &normal) > 0.0001)
		    normal = vector_scale(-1, &normal);
        *(t_color *)reflected_color = reflection_color(&intersection_point, &normal, &r->dir, object, light);
        return (1);
    }
    return (0);
}
