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

t_object *new_triangle(t_point *vertex, double specular, t_color color)
{
    t_triangle *new_triangle;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_triangle = malloc(sizeof(t_triangle));
    new_triangle->vertex = malloc(sizeof(t_point) * 3);
    new_triangle->vertex = vertex;
    new_object->specular = specular;
    new_object->color = color;
    new_object->data = (void *)new_triangle;
    new_object->tag = "triangle";
    new_object->intersect = &intersect_ray_triangle;
    return(new_object);
}
