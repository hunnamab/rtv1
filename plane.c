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
    new_plane->d = -new_plane->normal.x * new_plane->point.x - new_plane->normal.y * new_plane->point.y - new_plane->normal.z * new_plane->point.z;
    //printf("plane d %f\n", new_plane->d);
    return(new_object);
}

int intersect_ray_plane(t_ray *r, t_object *object, t_color *reflected_color, t_light **light)
{
    float k1;
    float k2;
    float t;
    t_plane *plane;
    t_point intersection_point;

    plane = (t_plane *)object->data;
    if ((vector_dot(&r->dir, &plane->normal)) == 0)
        return(0);
    k1 = vector_dot(&r->start, &plane->normal) + plane->d;
    k2 = vector_dot(&r->dir, &plane->normal);
    if (k1 == 0 || (k1 < 0 && k2 < 0) || (k1 > 0 && k2 > 0))
        return(0);
    t = -k1 / k2;
    intersection_point = vector_scale(t, &r->dir);
   /*  printf("plane.normal.x = %f, plane.normal.y %f, plane.normal.z %f\n", plane->normal.x, plane->normal.y, plane->normal.z);
    printf("first_part %f, second part %f\n", -k1, k2);
    printf("r.start.x %f, r.start.y %f, r.start.z %f, r.dir.x %f, r.dir.y %f, r.dir.z %f\n",r->start.x,r->start.y,r->start.z,r->dir.x,r->dir.y,r->dir.z);
    printf("int_p.x == %f int_p.y == %f int_p.z == %f t == %f\n",intersection_point.x, intersection_point.y, intersection_point.z, t); */
    if (vector_dot(&r->dir, &plane->normal) > 0.0001)
        plane->normal = vector_scale(-1, &plane->normal);
    *(t_color *)reflected_color = reflection_color(&intersection_point, &plane->normal, &r->dir, object, light);
    return (1);
}