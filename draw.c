#include "rtv1.h"

void zabei(t_sphere *s1, t_sphere *s2)
{
    s1->color.red = 0;
    s1->color.blue = 255;
    s2->color.red = 0;
    s2->color.green = 255;
}

void draw_sphere(t_sdl *sdl)
{
    t_ray r;
    t_object **s; //теперь создаем объект сферический
    int x;
    int y;
    int is_intersect;
    int sphere_num;
    int j = 200;
    int i = 0;
    float t0;
    float t1;
    t_color color;

    sphere_num = 3;
    s = malloc(sizeof(t_object *) * sphere_num);
    for (int f = 0; f < sphere_num; f++)
    {
        s[f] = new_sphere(get_point(j, (HEI/2 + j/5), j / 2), 90);
        j+= 200;
    }
    color.alpha = 255;
    zabei((t_sphere *)s[1]->data, (t_sphere *)s[2]->data);
//    s[1]->*(t_sphere *)data->color.red = 0; а вот так не могу, ток в функцию если передавать
//   s[1]->*(t_sphere *)data->color.blue = 255;
    sphere_settings((t_sphere *)s[0]->data, &r); //settings.c
    x = 0;
    y = 0;
    is_intersect = 0;
    while (y < HEI)
    {
        r.start.y = y;
        r.start.z = 0;
        while (x < WID)
        {
            r.start.x = x;
            while(i < sphere_num)
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
