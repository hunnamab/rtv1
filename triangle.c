#include "rtv1.h"

int intersect_ray_triangle(t_ray *r, t_object *object, t_color *reflected_color)
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
    float t;
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
    t = vector_dot(&edge2, &qvec) * inv_det;
    *(t_color *)reflected_color = object->color;
    return(1);
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
