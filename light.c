#include "rtv1.h"

t_light     *new_light(t_point position, t_point direction, const char *type)
{
    t_light *new_light;

    new_light = malloc(sizeof(t_light));
    new_light->type = ft_strcpy_alloc(new_light->type, type);
    if (ft_strequ(new_light->type, "point"))
        new_light->intensity = 0.2;
    else
        new_light->intensity = 0.2;
    new_light->position = position;
    new_light->direction = direction;
    return(new_light);
}

t_point     get_light_vec(t_scene *scene, int index, float *i, int j)
{
    t_point light_vec;

    light_vec = get_point(0,0,0);
    if (ft_strequ(scene->light[j]->type, "point"))
        light_vec = vector_sub(&scene->light[j]->position, &scene->intersection_buf[index]);
    if (ft_strequ(scene->light[j]->type, "directional"))
        light_vec = scene->light[j]->direction;
    return(light_vec);
}

int         in_shadow(t_scene *scene, int index, t_point *L)
{
    t_ray ray;
    int i;
    float t;
    float buf;

    i = 0;
    ray.start = scene->intersection_buf[index];
    ray.dir = *L;
    buf = 0;
    while (i < scene->obj_nmb && buf == 0)
    {
        buf = scene->objs[i]->intersect(&ray, scene->objs[i]);
        i++;
    }
    t = buf;
    while (i < scene->obj_nmb)
    {
        buf = scene->objs[i]->intersect(&ray, scene->objs[i]);
        if (t > buf && buf > 0)
            t = buf;
        i++;
    }
    if (t < 1 && t > 0.0001)
        return(1);
    return(0);
}

float       get_specular(t_scene *scene, int index, int j, t_point *L)
{
    float   r_dot_v;
    t_point R;
    t_point D;
    float   i;
    float   n_dot_l;

    i = 0;
    n_dot_l = vector_dot(&scene->normal_buf[index], L);
    R = vector_scale(2.0, &scene->normal_buf[index]);
    R = vector_scale(n_dot_l, &R);
    R = vector_sub(&R, L);
    D.x = -scene->ray_buf[index].dir.x;
    D.y = -scene->ray_buf[index].dir.y;
    D.z = -scene->ray_buf[index].dir.z;
    r_dot_v = vector_dot(&R, &D);
    if (r_dot_v > 0)
        i += scene->light[j]->intensity * pow((double)r_dot_v / (vector_length(&R) * vector_length(&D)), scene->material_buf[index].specular);
    return(i);
}

t_color     reflection_color(t_scene *scene, int index)
{
    float i;
    t_color result_color;
    t_point L;
    float n_dot_l;
    int j;

    j = 0;
    i = 0;
    while (j < scene->light_nmb)
    {
        if (ft_strequ(scene->light[j]->type, "ambient"))
            i += 0.2;
        else
        {
            L = get_light_vec(scene, index, &i, j);
            n_dot_l = vector_dot(&scene->normal_buf[index], &L);
            if (!in_shadow(scene, index, &L))
            {
                if (n_dot_l > 0)
                    i += (scene->light[j]->intensity * n_dot_l) / vector_length(&L);
                if (scene->material_buf[index].specular != -1)
                    i += get_specular(scene, index, j, &L);
            }
        }
        j++;
    }
    i = i > 1 ? 1 : i;
    return (color_mul_by_scalar(&scene->material_buf[index].color, i));
}
