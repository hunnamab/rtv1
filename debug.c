#include "rtv1.h"

void debug(t_sdl sdl)
{
    SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 255, 255);
    SDL_RenderDrawPoint(sdl.renderer, 612, 379);
    SDL_RenderPresent(sdl.renderer);
}
