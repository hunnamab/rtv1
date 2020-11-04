#include "rtv1.h"

t_object *new_cone(t_point position, float specular, t_color color)
{
    t_cone *new_cone;
    t_object *new_object;
    
    new_object = malloc(sizeof(t_object));
    new_cone = malloc(sizeof(t_triangle));
    new_cone->position = position;
    new_object->specular = specular;
    new_object->color = color;
    new_object->data = (void *)new_cone;
    new_object->tag = "cone";
    new_object->intersect = &intersect_ray_cone;
    new_object->get_normal = &get_cone_normal;
    return(new_object);
}

void    get_cone_normal(t_scene *scene, int index, int obj_num)
{
    t_cone *cone;
    float   n;
    t_point *normal;
    float radius;
    float height;

    radius = 1;
    height = 2;
    normal = &scene->normal_buf[index];
    cone = (t_cone *)scene->objs[obj_num]->data;
    normal->x = scene->intersection_buf[index].x - cone->position.x;
    normal->y = 0;
    normal->z = scene->intersection_buf[index].z - cone->position.z;
    n = sqrt((normal->x * normal->x) + (normal->z * normal->z));
    normal->x /= n;
    normal->z /= n;
    normal->x = normal->x * (height / radius);
    normal->y = radius / height;
    normal->z = normal->z * (height / radius);
}

float intersect_ray_cone(t_ray *r, t_object *object)
{
    float a;
    float b;
    float c;
    float discr;
    float sqrt_discr;
    float t0;
    float t1;
    t_point dist;
    t_cone *cone;

    cone = (t_cone *)object->data;
    float tan = ((float)1 / (float)2) * ((float)1 / (float)2);
    a = r->dir.x * r->dir.x + r->dir.z * r->dir.z - (tan * (r->dir.y * r->dir.y));
    dist = vector_sub(&r->start, &cone->position);
    dist.y = (float)2 - r->start.y + cone->position.y;
    b = 2 * dist.x * r->dir.x + 2 * dist.z * r->dir.z + (2 * tan * dist.y * r->dir.y);
    c = dist.x * dist.x + dist.z * dist.z - (tan * (dist.y * dist.y));
    discr = b * b - 4 * a * c;
    if (discr < 0)
        return (0);
    else
    {
        sqrt_discr = sqrt(discr);
        return (choose_t((-b + sqrt_discr) / (2 * a), (-b - sqrt_discr) / (2 * a)));
    }
    return (0);
}
