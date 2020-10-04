#include "rtv1.h"

void draw_objects(t_sdl *sdl, t_object **objs, int obj_nmb)
{
    t_ray r;
    float x;
    float y;
    int is_intersect;
    int i = 0;
    float t0;
    float t1;
    t_color color;
    t_light **light;
    float **transform_matrix;
    float *coord_matrix;

    coord_matrix = malloc(sizeof(float) * 4);
    transform_matrix = get_transform_matrix(get_three_floats(0.5, 0, 0), get_three_floats(0,0,0), get_three_floats(1,1,1));
    light = malloc(sizeof(t_light *) * 4);
    light[0] = new_light(get_point(0, 1000, 0), get_point(0, 0, 0), "point");
    light[1] = new_light(get_point(0, 50, 0), get_point(0, 0, 0), "point");
    light[2] = new_light(get_point(0, 0, 0), get_point(0, 0, 10), "ambient");
    light[3] = NULL;
    x = 0;
    y = 0;
    is_intersect = 0;
    r.start.y = 20;
    r.start.z = -10;
    r.start.x = 0;
    t_point view_port_point;
    view_port_point.z = r.start.z + 1;
    t_color buf;
    buf.red = 185;
    buf.green = 0;
    buf.blue = 70;
    buf.alpha = 255;
    //objs[obj_nmb] = new_plane(get_point(0,0,1), get_point(0,0.3,1), -1, buf);
    //obj_nmb += 1;
    //i = obj_nmb - 1;
    while (y < HEI)
    {
        view_port_point.y = -(y - (float)HEI / 2) * (1 / (float)HEI) + r.start.y;
        while (x < WID)
        {
            view_port_point.x = (x - (float)WID / 2) * (((float)WID / (float)HEI)/ (float)WID) + r.start.x;
            r.dir = vector_sub(&view_port_point, &r.start);
            transform(&r.dir, transform_matrix, coord_matrix, 1);
            while(i < obj_nmb)
            {
                is_intersect = objs[i]->intersect(&r, objs[i], &color, light);
                if (is_intersect)
                {
                    SDL_SetRenderDrawColor(sdl->renderer, color.red, color.green, color.blue, color.alpha);
                    SDL_RenderDrawPoint(sdl->renderer, x, y);
                    break;
                }
                else
                {
                    SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
                    SDL_RenderDrawPoint(sdl->renderer, x, y);
                }
                i++;
            }
            x++;
            is_intersect = 0;
            i = 0;
        }
        x = 0;
        y++;
    }
    SDL_RenderPresent(sdl->renderer);
}
