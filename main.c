#include "rtv1.h"

int main(int args, char **argv)
{
    int     fd;
    t_sdl   sdl;

    /*if (args != 2)
    {
        ft_putstr("usage: ./rtv1 [scene_file]\n");
        return (0);
    }
    else
    {
        fd = open(argv[1], O_RDONLY);
        read_scene(fd);
        return (0);
    }*/
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WID, HEI, 0, &sdl.win, &sdl.renderer);
    SDL_RenderClear(sdl.renderer);
    draw_sphere(&sdl); //draw.c
    while (1)
    {
        if (SDL_PollEvent(&sdl.event))
        {
            if (SDL_QUIT == sdl.event.type || SDLK_ESCAPE == sdl.event.key.keysym.sym)
                break ;
        }
    }
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.win);
    SDL_Quit();
    return (0);
}
