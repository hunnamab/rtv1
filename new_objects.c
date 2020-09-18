#include "rtv1.h"

t_object *new_sphere(t_point center, int16_t radius)
{
    t_sphere *new_sphere;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_sphere = malloc(sizeof(t_sphere));
    new_sphere->center = center;
    new_sphere->radius = radius;
    new_object->specular = 50.0;
    new_object->color.red = 255;
    new_object->color.green = 0;
    new_object->color.blue = 0;
    new_object->color.alpha = 255;
    new_object->data = (void *)new_sphere;
    new_object->tag = "sphere";
    new_object->intersect = &intersect_ray_sphere;
    return(new_object);
}

t_object *new_triangle(t_point v1, t_point v2, t_point v3)
{
    t_triangle *new_triangle;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_triangle = malloc(sizeof(t_triangle));
    new_triangle->vertex = malloc(sizeof(t_point) * 3);
    new_triangle->vertex[0] = v1;
    new_triangle->vertex[1] = v2;
    new_triangle->vertex[2] = v3;
    new_object->specular = 50.0;
    new_object->color.red = 255;
    new_object->color.green = 0;
    new_object->color.blue = 0;
    new_object->color.alpha = 255;
    new_object->data = (void *)new_triangle;
    new_object->tag = "triangle";
    new_object->intersect = &intersect_ray_triangle;
    return(new_object);
}
