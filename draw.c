#include "rtv1.h"

void draw_objects(t_sdl *sdl, t_object **objs, int obj_nmb, t_light **light, int light_nmb, t_ray *r)
{
    int x;
    int y;
    int is_intersect;
    int i = 0;
    float t;
    float t_buf;
    t_color *color;
    float **transform_matrix;
    float *coord_matrix;
    t_point *normal;
    t_point intersection_point;
    t_color **normal_map;
    t_point *normal_buf;
    int p;
    int buf_i;

    p = 0;
    color = malloc(sizeof(t_color));
    normal = malloc(sizeof(t_point));
    normal_buf = malloc(sizeof(t_point));
    coord_matrix = malloc(sizeof(float) * 4);
    transform_matrix = get_transform_matrix(get_three_floats(0, 0, 0), get_three_floats(0,0,0), get_three_floats(1,1,1));
    x = 0;
    y = 0;
    is_intersect = 0;
    t = 0;
    t_buf = 0;
    intersection_point = get_point(0,0,0);
    buf_i = 0;
    while (y < HEI)
    {
        while (x < WID)
        {
            transform(&r[y * WID + x].dir, transform_matrix, coord_matrix, 1);
            while(i < obj_nmb)
            {
                is_intersect = objs[i]->intersect(&r[y * WID + x], objs[i], normal, &t);
                if (is_intersect)
                    break;
                i++;
            }
            buf_i = i;
            t_buf = t;
            copy_point(normal_buf, normal);
            while(i < obj_nmb)
            {
                is_intersect = objs[i]->intersect(&r[y * WID + x], objs[i], normal, &t);
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
                intersection_point = vector_scale(t_buf, &r[y * WID + x].dir);
                intersection_point = vector_add(&r[y * WID + x].start, &intersection_point);
                *(t_color *)color = reflection_color(&intersection_point, normal_buf, &r[y * WID + x].dir, objs[buf_i], light, light_nmb);
                //SDL_SetRenderDrawColor(sdl->renderer, color->red, color->green, color->blue, color->alpha);
                //SDL_SetRenderDrawColor(sdl->renderer, normal_buf[0].x, normal_buf[0].y, normal_buf[0].z, 255);
                SDL_RenderDrawPoint(sdl->renderer, x, y);
            }
            x++;
            t = 0;
            t_buf = 0;
            i = 0;
        }
        x = 0;
        y++;
    }
    SDL_RenderPresent(sdl->renderer);
}

void    new_draw(t_point *normal_buf, t_color *color_buf, t_point *intersection_buf, t_ray *r, t_sdl *sdl, t_light **light, int light_nmb)
{
    int x;
    int y;
    t_color *color;
    int i;


    color = malloc(sizeof(t_color));
    x = 0;
    y = 0;
    i = 0;
    while (y < HEI)
    {
        while (x < WID)
        {
            i = y * WID + x;
            *(t_color *)color = reflection_color_new(&intersection_buf[i], &normal_buf[i], &r[i].dir, &color_buf[i], light, light_nmb);
            //SDL_SetRenderDrawColor(sdl->renderer, color_buf[i].red, color_buf[i].green, color_buf[i].blue, color_buf[i].alpha);
            //SDL_SetRenderDrawColor(sdl->renderer, normal_buf[i].x * 100, normal_buf[i].y * 100, normal_buf[i].z * 100, 255);
            //SDL_SetRenderDrawColor(sdl->renderer, intersection_buf[i].x * 100, intersection_buf[i].y * 100, intersection_buf[i].z * 100, 255);
            //printf("color.r %u, color.g %u, color.b %u, color.a %u\n,", color_buf[i].red, color_buf[i].green, color_buf[i].blue, color_buf[i].alpha);
            SDL_SetRenderDrawColor(sdl->renderer, color->red, color->green, color->blue, color->alpha);
            SDL_RenderDrawPoint(sdl->renderer, x, y);
            x++;
        }
        x = 0;
        y++;
    }
    SDL_RenderPresent(sdl->renderer);
}