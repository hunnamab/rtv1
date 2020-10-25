#include "rtv1.h"

void    get_sphere_normal(t_scene *scene, int index, int obj_num)
{
    t_sphere *s;


    s = (t_sphere *)scene->objs[obj_num]->data;
    scene->normal_buf[index] = vector_sub(&scene->intersection_buf[index], &s->center);
    scene->normal_buf[index] = vector_div_by_scalar(&scene->normal_buf[index], vector_length(&scene->normal_buf[index]));
}

void    get_plane_normal(t_scene *scene, int index, int obj_num)
{
    t_plane *p;

    p = (t_plane *)scene->objs[obj_num]->data;
    copy_point(&scene->normal_buf[index], &p->normal);
    if (vector_dot(&scene->ray_buf[index].dir, &scene->normal_buf[index]) > 0.0001)
        scene->normal_buf[index] = vector_scale(-1, &scene->normal_buf[index]);
}

void    get_triangle_normal(t_scene *scene, int index, int obj_num)
{
    t_triangle *t;

    t = (t_triangle *)scene->objs[obj_num]->data;
    copy_point(&scene->normal_buf[index], &t->normal);
    if (vector_dot(&scene->ray_buf[index].dir, &scene->normal_buf[index]) > 0.0001)
        scene->normal_buf[index] = vector_scale(-1, &scene->normal_buf[index]);
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

void    get_cylinder_normal(t_scene *scene, int index, int obj_num)
{
    t_cylinder *cylinder;
    t_point *normal;

    normal = &scene->normal_buf[index];
    cylinder = (t_cylinder *)scene->objs[obj_num]->data;
    *normal = vector_sub(&scene->intersection_buf[index], &cylinder->position);
    normal->y = 0;
    normalize_vector(&normal);
    scene->normal_buf[index] = vector_div_by_scalar(&scene->normal_buf[index], vector_length(&scene->normal_buf[index]));
}