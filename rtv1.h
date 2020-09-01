#ifndef RTV1_H
# define RTV1_H

//# include "SDL2.framework/Headers/SDL.h" //for macOS
# include <SDL2/SDL.h> //for linux
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft.h"
# include <unistd.h>
# define HEI 1024
# define WID 1024
typedef struct 		sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
}                	t_sdl;

void	julia(t_sdl sdl);

#endif
