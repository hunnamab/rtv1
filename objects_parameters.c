#include "rtv1.h"

t_object *get_sphere(char *description)
{
    t_object *sphere;
    t_point center;
    int16_t radius;

    sphere = malloc(sizeof(t_object));
    sphere = new_sphere(center, radius);
}

t_object *get_triangle(char *description)
{
    t_object *triangle;
    t_point v1;
    t_point v2;
    t_point v3;

    triangle = malloc(sizeof(t_object));
    triangle = new_triangle(v1, v2, v3);
}
