#include "rtv1.h"

void    	draw_scene(t_sdl *sdl, t_scene *scene)
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
            if(scene->index_buf[i] != -1)
            {
                *(t_color *)color = reflection_color(scene, i);
                SDL_SetRenderDrawColor(sdl->renderer, color->red, color->green, color->blue, color->alpha);
                SDL_RenderDrawPoint(sdl->renderer, x, y);
            }
            x++;
        }
        x = 0;
        y++;
    }
    SDL_RenderPresent(sdl->renderer);
}

void    draw_normal_buf(t_sdl *sdl, t_scene *scene)
{
    int x;
    int y;
    int i;


    x = 0;
    y = 0;
    i = 0;
    while (y < HEI)
    {
        while (x < WID)
        {
            i = y * WID + x;
            if(scene->index_buf[i] != -1)
            {
                SDL_SetRenderDrawColor(sdl->renderer, scene->normal_buf[i].x * 100, scene->normal_buf[i].y * 100, scene->normal_buf[i].z * 100, 255);
                SDL_RenderDrawPoint(sdl->renderer, x, y);
            }
            x++;
        }
        x = 0;
        y++;
    }
    SDL_RenderPresent(sdl->renderer);
}