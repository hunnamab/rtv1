#include "rtv1.h"

void draw_objects(t_sdl *sdl, t_object **objs, int obj_nmb)
{
    t_ray r;
    //t_object **s; //теперь создаем объект сферический
    float x;
    float y;
    int is_intersect;
    //int j = 200;
    int i = 0;
    float t0;
    float t1;
    t_color color;

    /* obj_num = 4;
    s = malloc(sizeof(t_object *) * obj_num);
    s[0] = new_sphere(get_point(0, 0, 10), 1);
    s[1] = new_sphere(get_point(1, 1, 5), 1);
    s[1]->color = get_color(0, 255, 0, 255);
    s[2] = new_sphere(get_point(1, -1, 3), 1);
    s[2]->color = get_color(0, 0, 255, 255);
    s[3] = new_triangle(get_point(-1, 1, 10), get_point(1, 1, 10), get_point(-1, -1, 10));
    s[3]->color = get_color(255, 0, 255, 255); */
    x = 0;
    y = 0;
    is_intersect = 0;
    r.start.y = 0;
    r.start.z = 0;
    r.start.x = 0;
    t_point view_port_point;
    view_port_point.z = 1;
    while (y < HEI)
    {
        view_port_point.y = -(y - (float)HEI / 2) * (1 / (float)HEI);
        while (x < WID)
        {
            view_port_point.x = (x - (float)WID / 2) * (1 / (float)WID);
            r.dir = vector_sub(&view_port_point, &r.start);
            while(i < obj_nmb)
            {
                is_intersect = objs[i]->intersect(&r, objs[i], &color);
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
