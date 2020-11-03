#include "rtv1.h"

t_object *new_triangle(t_point *vertex, double specular, t_color color)
{
    t_triangle  *new_triangle;
    t_object    *new_object;
    t_point     edge1;
    t_point     edge2;

    new_object = malloc(sizeof(t_object));
    new_triangle = malloc(sizeof(t_triangle));
    new_triangle->vertex = malloc(sizeof(t_point) * 3);
    new_triangle->vertex = vertex;
    edge1 = vector_sub(&new_triangle->vertex[0], &new_triangle->vertex[1]);
    edge2 = vector_sub(&new_triangle->vertex[1], &new_triangle->vertex[2]);
    new_triangle->normal = vector_cross(&edge1, &edge2);
    normalize_vector(&new_triangle->normal);
    new_object->specular = specular;
    new_object->color = color;
    new_object->data = (void *)new_triangle;
    new_object->tag = "triangle";
    new_object->intersect = &intersect_ray_triangle;
    new_object->get_normal = &get_triangle_normal;
    return(new_object);
}

void    get_triangle_normal(t_scene *scene, int index, int obj_num)
{
    t_triangle *t;

    t = (t_triangle *)scene->objs[obj_num]->data;
    copy_point(&scene->normal_buf[index], &t->normal);
    if (vector_dot(&scene->ray_buf[index].dir, &scene->normal_buf[index]) > 0.0001)
        scene->normal_buf[index] = vector_scale(-1, &scene->normal_buf[index]);
}

float intersect_ray_triangle(t_ray *r, t_object *object)
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
    return (vector_dot(&edge2, &qvec) * inv_det);
}
