#include "rtv1.h"

void draw_objects(t_sdl *sdl, t_object **objs, int obj_nmb, t_light **light, int light_nmb)
{
    t_ray r;
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
    int p;
    int buf_i;
    t_point *viewport;
    t_camera camera;

    camera.pos = get_point(-10, 25, -20);
    p = 0;
    color = malloc(sizeof(t_color));
    normal = malloc(sizeof(t_point));
    coord_matrix = malloc(sizeof(float) * 4);
    transform_matrix = get_transform_matrix(get_three_floats(0, 0, 0), get_three_floats(0,0,0), get_three_floats(1,1,1));
    x = 0;
    y = 0;
    is_intersect = 0;
    t = 0;
    t_buf = 0;
    intersection_point = get_point(0,0,0);
    viewport = get_viewport_coords(&camera);
    r.start.x = camera.pos.x;
    r.start.y = camera.pos.y;
    r.start.z = camera.pos.z;
    buf_i = 0;
    while (y < HEI)
    {
        while (x < WID)
        {
            r.dir = vector_sub(&view_port[y * HEI + x], &r.start);
            transform(&r.dir, transform_matrix, coord_matrix, 1);
            while(i < obj_nmb)
            {
                is_intersect = objs[i]->intersect(&r, objs[i], normal, &t);
                if (is_intersect)
                    break;
                i++;
            }
            buf_i = i;
            t_buf = t;
            while(i < obj_nmb)
            {
                is_intersect = objs[i]->intersect(&r, objs[i], normal, &t);
                if (t < t_buf)
                {
                    t_buf = t;
                    buf_i = i;
                }
                i++;
            } 
            if (t_buf)
            {
                intersection_point = vector_scale(t_buf, &r.dir);
                intersection_point = vector_add(&r.start, &intersection_point);
                *(t_color *)color = reflection_color(&intersection_point, normal, &r.dir, objs[buf_i], light, light_nmb);
                SDL_SetRenderDrawColor(sdl->renderer, color->red, color->green, color->blue, color->alpha);
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
