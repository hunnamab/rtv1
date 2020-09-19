#include "rtv1.h"

void draw_sphere(t_sdl *sdl)
{
    t_ray r;
    t_object **s; //теперь создаем объект сферический
    int x;
    int y;
    int is_intersect;
    int obj_num;
    int j = 200;
    int i = 0;
    float t0;
    float t1;
    t_color color;

    obj_num = 4;
    s = malloc(sizeof(t_object *) * obj_num);
    s[0] = new_sphere(get_point(0, -1, 0.00001), 1);
    for (int f = 1; f < 3; f++)
    {
        s[f] = new_sphere(get_point(j, (HEI/2 + j), j / 2), 60); // new_objects.c
        j+= 200;
    }
    color.alpha = 255;
    s[1]->color.red = 0;
    s[1]->color.blue = 255;
    s[2]->color.red = 0;
    s[2]->color.green = 255;
    s[3] = new_triangle(get_point(600, 600, 200), get_point(400, 400, 200), get_point(600, 400, 200)); // new_objects.c
    //s[3] = new_sphere(get_point(100, 100, 100), 90);
   // sphere_settings((t_sphere *)s[0]->data, &r); //settings.c
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
        view_port_point.y = -(y - HEI / 2) * (1 / HEI);
        while (x < WID)
        {
            view_port_point.x = (x - WID / 2) * (1 / WID);
            r.dir = vector_sub(&view_port_point, &r.start);
            while(i < 1)
            {
                is_intersect = s[i]->intersect(&r, s[i], &color); //sphere.c
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
