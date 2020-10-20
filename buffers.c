#include "rtv1.h"
#include <unistd.h>
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

t_point     *get_buffers(t_object **obj, int obj_nmb, t_ray *r, t_point *normal_buffer, t_color *color_buf)
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
    t_point *intersection_buffer;

    intersection_buffer = malloc(sizeof(t_point) * (WID * HEI) + 1);
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
            while(i < obj_nmb)
            {
                is_intersect = obj[i]->intersect(&r[y * WID + x], obj[i], normal, &t);
                if (is_intersect)
                    break;
                i++;
            }
            buf_i = i;
            t_buf = t;
            copy_point(normal_buf, normal);
            while(i < obj_nmb)
            {
                is_intersect = obj[i]->intersect(&r[y * WID + x], obj[i], normal, &t);
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
                copy_point(&normal_buffer[y * WID + x], normal_buf);
                intersection_buffer[y * WID + x] = vector_scale(t_buf, &r[y * WID + x].dir);
                intersection_buffer[y * WID + x] = vector_add(&r[y * WID + x].start, &intersection_buffer[y * WID + x]);
                copy_color(&color_buf[y * WID + x], &obj[buf_i]->color);
            }
            else
            {
                normal_buffer[y * WID + x] = get_point(0,0,0);
                intersection_buffer[y * WID + x] = get_point(0,0,0);
                set_color_zero(&color_buf[y * WID + x]);
            }
            x++;
            t = 0;
            t_buf = 0;
            i = 0;
        }
        x = 0;
        y++;
    }
    return(intersection_buffer);
}