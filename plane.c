#include "rtv1.h"

t_object *new_plane(t_point point, t_point normal, float specular, t_color color)
{
    t_plane *new_plane;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_plane = malloc(sizeof(t_plane));
    new_plane->normal = normal;
    normalize_vector(&new_plane->normal);
    new_plane->point = point;
    new_object->specular = specular;
    new_object->color = color;
    new_object->data = (void *)new_plane;
    new_object->tag = "plane";
    new_object->intersect = &intersect_ray_plane;
    new_object->get_normal = &get_plane_normal;
    new_plane->d = -new_plane->normal.x * new_plane->point.x - new_plane->normal.y * new_plane->point.y - new_plane->normal.z * new_plane->point.z;
    return(new_object);
}

float intersect_ray_plane(t_ray *r, t_object *object, t_point *normal)
{
    float k1;
    float k2;
    t_plane *plane;

    plane = (t_plane *)object->data;
    if ((vector_dot(&r->dir, &plane->normal)) == 0)
        return(0);
    k1 = vector_dot(&r->start, &plane->normal) + plane->d;
    k2 = vector_dot(&r->dir, &plane->normal);
    if (k1 == 0 || (k1 < 0 && k2 < 0) || (k1 > 0 && k2 > 0))
        return(0);
    return (-k1 / k2);
}