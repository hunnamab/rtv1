#include "rtv1.h"

void draw_sphere(t_sdl *sdl)
{
    t_ray r;
    t_sphere **s;
    int x;
    int y;
    int is_intersect;
    int sphere_num; 
    int j = 200;
    int i = 0;

    sphere_num = 3;
    s = malloc(sizeof(t_sphere *) * sphere_num);
    for(int i = 0; i < sphere_num; i++)
    {
        s[i] = new_sphere(get_point(j, HEI/2, j), 80);
        j+= 200;
    }
    sphere_settings(s[0], &r); //settings.c
    x = 0;
    y = 0;
    is_intersect = 0;
    while (y < HEI)
    {
        r.start.y = y;
        while (x < WID)
        {
            r.start.x = x;
            while(i < sphere_num)
            {
                is_intersect = intersect_ray_sphere(&r, s[i], 0); //sphere.c
                if (is_intersect)
                    break;
                i++;
            }
            if (is_intersect)
            {
                SDL_SetRenderDrawColor(sdl->renderer, 255, 0, 0, 255);
                SDL_RenderDrawPoint(sdl->renderer, x, y);
            }
            else
            {
                SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
                SDL_RenderDrawPoint(sdl->renderer, x, y);
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
