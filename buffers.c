#include "rtv1.h"

t_ray *get_rays_arr(t_camera *camera, t_point *viewport)
{
    int x;
    int y;
    t_ray *rays;

    rays = malloc(sizeof(t_ray) * (WID * HEI));
    x = 0;
    y = 0;
    while(y < HEI)
    {
        while(x < WID)
        {
            rays[y * WID + x].start.x = camera->position.x;
            rays[y * WID + x].start.y = camera->position.y;
            rays[y * WID + x].start.x = camera->position.z;
            rays[y * WID + x].dir = vector_sub(&viewport[y * WID + x], &camera->position);
            x++;
        }
        x = 0;
        y++;
    }
    return(rays);
}

void     get_buffers(t_scene *scene)
{
    int x;
    int y;
    int is_intersect;
    int i;
    float t;
    float t_buf;
    int buf_i;
    t_point *normal;
    t_point *normal_buf;

    normal = malloc(sizeof(t_point));
    normal_buf = malloc(sizeof(t_point));
    t = 0;
    t_buf = 0;
    i = 0;
    buf_i = 0;
    is_intersect = 0;
    x = 0;
    y = 0;
    *normal = get_point(0,0,0);
    *normal_buf = get_point(0,0,0);
    while (y < HEI)
    {
        while (x < WID)
        {
            while(i < scene->obj_nmb)
            {
                is_intersect = scene->objs[i]->intersect(&scene->ray_buf[y * WID + x], scene->objs[i], normal, &t);
                if (is_intersect)
                    break;
                i++;
            }
            buf_i = i;
            t_buf = t;
            copy_point(normal_buf, normal);
            while(i < scene->obj_nmb)
            {
                is_intersect = scene->objs[i]->intersect(&scene->ray_buf[y * WID + x], scene->objs[i], normal, &t);
                if (t < t_buf)
                {
                    copy_point(normal_buf, normal);
                    t_buf = t;
                    buf_i = i;
                }
                i++;
            }
            if (t_buf)
            {
                copy_point(&scene->normal_buf[y * WID + x], normal_buf);
                scene->intersection_buf[y * WID + x] = vector_scale(t_buf, &scene->ray_buf[y * WID + x].dir);
                scene->intersection_buf[y * WID + x] = vector_add(&scene->ray_buf[y * WID + x].start, &scene->intersection_buf[y * WID + x]);
                copy_color(&scene->material_buf[y * WID + x].color, &scene->objs[buf_i]->color);
                scene->material_buf[y * WID + x].specular = scene->objs[buf_i]->specular;
            }
            else
            {
                scene->normal_buf[y * WID + x] = get_point(0,0,0);
                scene->intersection_buf[y * WID + x] = get_point(0,0,0);
                set_color_zero(&scene->material_buf[y * WID + x].color);
                scene->material_buf[y * WID + x].specular = -1;
            }
            x++;
            t = 0;
            t_buf = 0;
            i = 0;
        }
        x = 0;
        y++;
    }
    i = 0;
}