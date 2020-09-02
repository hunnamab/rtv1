#include "rtv1.h"

void draw_sphere(t_sdl *sdl)
{
    t_ray r;
    t_sphere s;
    int x;
    int y;
    int is_intersect;

    sphere_settings(&s, &r); //settings.c
    x = 0;
    y = 0;
    is_intersect = 0;
    while (y < HEI)
    {
        r.start.y = y;
        while (x < WID)
        {
            r.start.x = x;
            is_intersect = intersect_ray_sphere(&r, &s, 0); //sphere.c
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
        }
        x = 0;
        y++;
    }
    SDL_RenderPresent(sdl->renderer);
}
