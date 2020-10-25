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
    new_object->get_normal = &get_cylinder_normal;
    return(new_object);
}

float intersect_ray_cylinder(t_ray *r, t_object *object)
{
    float a;
    float b;
    float c;
    float discr;
    float sqrt_discr;
    float t0;
    float t1;
    t_point dist;
    t_cylinder *cylinder;

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
        return (t1 < t0 ? t1 : t0);
    }
    return (0);
}
