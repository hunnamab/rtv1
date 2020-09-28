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
    return(new_object);
}

int intersect_ray_plane(t_ray *r, t_object *object, t_color *reflected_color, t_light **light)
{
    float d;
    float t;
    t_plane *plane;
    t_point intersection_point;

    plane = (t_plane *)object->data;
    if ((vector_dot(&r->dir, &plane->normal)) == 0)
        return(0);
    d = -plane->normal.x - plane->normal.y - plane->normal.z;
    t = -(plane->normal.x * r->start.x + plane->normal.y * r->start.y + plane->normal.z * r->start.z + d) \
    / r->dir.x * plane->normal.x + r->dir.y * plane->normal.y + r->dir.z * plane->normal.z;
    intersection_point = vector_scale(t, &r->start);
    *(t_color *)reflected_color = reflection_color(&intersection_point, &plane->normal, &r->dir, object, light);
    return (1);
}
