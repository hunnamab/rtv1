#include "rtv1.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *win;
    SDL_Renderer *renderer;
    SDL_Event win_event;
    t_sdl       sdl_components;

    SDL_CreateWindowAndRenderer(HEI, WID, 0, &win, &renderer);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    sdl_components.win = win;
    sdl_components.renderer = renderer;
    julia(sdl_components);
    while (1)
    {
        if (SDL_PollEvent(&win_event))
        {
            if (SDL_QUIT == win_event.type)
                break ;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return (0);
}
