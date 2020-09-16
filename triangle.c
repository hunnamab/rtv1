#include "rtv1.h"

int intersect_ray_triangle(t_ray *r, t_object *object, t_color *reflected_color)
{
    return(0);
}

t_object *new_triangle(t_point v1, t_point v2, t_point v3)
{
    t_triangle *new_triangle;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_triangle = malloc(sizeof(new_triangle));
    new_triangle->vertex[0] = v1;
    new_triangle->vertex[1] = v2;
    new_triangle->vertex[2] = v3;
    new_triangle->specular = 50.0;
    new_triangle->color.red = 255;
    new_triangle->color.green = 0;
    new_triangle->color.blue = 0;
    new_triangle->color.alpha = 255;
    new_object->data = (void *)new_triangle;
    new_object->tag = "triangle";
    new_object->intersect = &intersect_ray_triangle;
    return(new_object);
}
