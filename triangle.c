#include "rtv1.h"

t_object *new_triangle(t_point *vertex, double specular, t_color color)
{
    t_triangle *new_triangle;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_triangle = malloc(sizeof(t_triangle));
    new_triangle->vertex = malloc(sizeof(t_point) * 3);
    new_triangle->vertex = vertex;
    new_triangle->normal = vector_cross(&new_triangle->vertex[0], &new_triangle->vertex[1]);
    new_object->specular = specular;
    new_object->color = color;
    new_object->data = (void *)new_triangle;
    new_object->tag = "triangle";
    new_object->intersect = &intersect_ray_triangle;
    return(new_object);
}

int intersect_ray_triangle(t_ray *r, t_object *object, t_point *normal, float *t)
{
    t_triangle *triangle;
    t_point edge1;
    t_point edge2;
    t_point pvec;
    float det;
    float inv_det;
    t_point tvec;
    t_point qvec;
    float u;
    float v;
    t_point intersection_point;
    t_point buf;

    triangle = (t_triangle *)object->data;
    edge1 = vector_sub(&triangle->vertex[1], &triangle->vertex[0]);
    edge2 = vector_sub(&triangle->vertex[2], &triangle->vertex[0]);
    pvec = vector_cross(&r->dir, &edge2);
    det = vector_dot(&edge1, &pvec);
    if (det < 1e-8 && det > -1e-8)
        return(0);
    inv_det = 1 / det;
    tvec = vector_sub(&r->start, &triangle->vertex[0]);
    u = vector_dot(&tvec, &pvec) * inv_det;
    if (u < 0 || u > 1)
        return(0);
    qvec = vector_cross(&tvec, &edge1);
    v = vector_dot(&r->dir, &qvec) * inv_det;
    if (v < 0 || u + v > 1)
        return (0);
    *t = vector_dot(&edge2, &qvec) * inv_det;
    buf = vector_scale(*t, &r->dir);
/*     intersection_point = vector_add(&r->start, &buf); */
    normal->x = triangle->normal.x;
    normal->y = triangle->normal.y;
    normal->z = triangle->normal.z;
   /*  *(t_color *)reflected_color = reflection_color(&intersection_point, &normal, &r->dir, object, light, light_nmb); */
    return (1);
}
