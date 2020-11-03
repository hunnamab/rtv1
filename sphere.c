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
    new_object->get_normal = &get_sphere_normal;
    return(new_object);
}

void    get_sphere_normal(t_scene *scene, int index, int obj_num)
{
    t_sphere *s;


    s = (t_sphere *)scene->objs[obj_num]->data;
    scene->normal_buf[index] = vector_sub(&scene->intersection_buf[index], &s->center);
    scene->normal_buf[index] = vector_div_by_scalar(&scene->normal_buf[index], vector_length(&scene->normal_buf[index]));
    if (vector_dot(&scene->ray_buf[index].dir, &scene->normal_buf[index]) > 0.0001)
        scene->normal_buf[index] = vector_scale(-1, &scene->normal_buf[index]);
}

float   get_result(float t1, float t0)
{
    float result;

    result = 0;
    if (t1 < t0 && t1 > 0)
        result = t1;
    if (t0 < t1 && t0 > 0)
        result = t0;
    return(result);
}

float intersect_ray_sphere(t_ray *r, t_object *object)
{
    float a;
    float b;
    float c;
    float discr;
    float sqrt_discr;
    float t0;
    float t1;
    float res;
    t_point dist;
    t_sphere *s;
 
    s = (t_sphere *)object->data;
    a = vector_dot(&r->dir, &r->dir);
    dist = vector_sub(&r->start, &s->center);
    b = 2 * vector_dot(&dist, &r->dir);
    c = vector_dot(&dist, &dist) - (s->radius * s->radius);
    discr = b * b - 4 * a * c;
    if (discr < 0)
        return (0);
    else
    {
        sqrt_discr = sqrt(discr);
        t0 = (-b + sqrt_discr) / (2 * a);
        t1 = (-b - sqrt_discr) / (2 * a);
        return(get_result(t1, t0));
    }
    return (0);
}
