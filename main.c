#include "rtv1.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Event win_event;
    while (1)
    {
        if (SDL_PollEvent(&win_event))
        {
            if (SDL_QUIT == win_event.type)
                break ;
        }
    }
    SDL_DestroyWindow(win);
    return (0);
}
