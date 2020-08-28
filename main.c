#include "rtv1.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *win;
    SDL_Renderer *renderer;
    SDL_Event win_event;

    SDL_CreateWindowAndRenderer(900, 900, 0, &win, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, 450, 450);
    SDL_RenderPresent(renderer);
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
