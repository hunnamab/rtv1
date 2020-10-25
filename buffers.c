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

void     get_closest_points(t_scene *scene)
{
    int x;
    int y;
    float t;
    int i;
    int j;

    i = 0;
    t = 0;
    x = 0;
    y = 0;
    while (y < HEI)
    {
        while (x < WID)
        {
            j = y * WID + x;
            while(i < scene->obj_nmb)
            {
                t = scene->objs[i]->intersect(&scene->ray_buf[j], scene->objs[i]);
                if (t)
                    break;
                i++;
            }
            scene->index_buf[j] = i;
            scene->depth_buf[j] = t;
            while(i < scene->obj_nmb)
            {
                t = scene->objs[i]->intersect(&scene->ray_buf[j], scene->objs[i]);
                if (t < scene->depth_buf[j] && t != 0)
                {
                    scene->depth_buf[j] = t;
                    scene->index_buf[j] = i;
                }
                i++;
            }
            if (scene->depth_buf[j] == 0)
                scene->index_buf[j] = -1;
            x++;
            i = 0;
            t = 0;
        }
        x = 0;
        y++;
    }
}

void    get_intersection_buf(t_scene *scene)
{
    int x;
    int y;
    int i;

    x = 0;
    y = 0;
    while (y < HEI)
    {
        while (x < WID)
        {   
            i = y * WID + x;
            if (scene->index_buf[i] != -1)
            {
                scene->intersection_buf[i] = vector_scale(scene->depth_buf[i], &scene->ray_buf[i].dir);
                scene->intersection_buf[i] = vector_add(&scene->intersection_buf[i], &scene->ray_buf[i].start);
            }
            x++;
        }
        x = 0;
        y++;
    }
}

void    get_normal_buf(t_scene *scene)
{
    int x;
    int y;
    int i;
    int j;

    j = 0;
    x = 0;
    y = 0;
    while (y < HEI)
    {
        while (x < WID)
        {   
            i = y * WID + x;
            if (scene->index_buf[i] != -1)
            {
                j = scene->index_buf[i];
                scene->objs[j]->get_normal(scene, i, j);
            }
            x++;
        }
        x = 0;
        y++;
    }
}

void    get_material_buf(t_scene *scene)
{
    int x;
    int y;
    int i;
    int j;

    j = 0;
    x = 0;
    y = 0;
    while (y < HEI)
    {
        while (x < WID)
        {   
            i = y * WID + x;
            if (scene->index_buf[i] != -1)
            {
                j = scene->index_buf[i];
                copy_color(&scene->material_buf[i], &scene->objs[j]->color);
                scene->material_buf[i].specular = scene->objs[j]->specular;
            }
            else
            {
                set_color_zero(&scene->material_buf[i].color);
                scene->material_buf[i].specular = -1;
            }   
            x++;
        }
        x = 0;
        y++;
    }
}