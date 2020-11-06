#include "rtv1.h"

void    	draw_scene(t_sdl *sdl, t_scene *scene)
{
    int x;
    int y;
    t_color color;
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
                color = reflection_color(scene, i);
            else
                set_color_zero(&color);
            SDL_SetRenderDrawColor(sdl->renderer, color.red, color.green, color.blue, 255);
            SDL_RenderDrawPoint(sdl->renderer, x, y);
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
    t_color color;

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
                color.red = (scene->normal_buf[i].x * 0.5 + 0.5) * 100;
                color.green = (scene->normal_buf[i].y * 0.5 + 0.5) * 100;
                color.blue = (scene->normal_buf[i].z * 0.5 + 0.5) * 100;
            }
            else
                set_color_zero(&color);
            SDL_SetRenderDrawColor(sdl->renderer, color.red, color.green, color.blue, 255);
            SDL_RenderDrawPoint(sdl->renderer, x, y);
            x++;
        }
        x = 0;
        y++;
    }
    SDL_RenderPresent(sdl->renderer);
}