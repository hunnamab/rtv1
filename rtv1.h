#ifndef RTV1_H
# define RTV1_H

# include "SDL2.framework/Headers/SDL.h" //for macOS
//# include <SDL2/SDL.h> //for linux
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdint.h>
# include "libft.h"
# include <unistd.h>
# include <stdint.h>

# define HEI 768
# define WID 1024

typedef struct 		sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Event		event;
}                	t_sdl;

typedef struct		point
{
	int16_t x;
	int16_t y;
	int16_t z;
}					t_point;

typedef	struct 		color
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	uint8_t			alpha;
}					t_color;

typedef	struct 		sphere
{
	t_point			center;
	int16_t			radius;
	t_color			color;
}					t_sphere;


void	julia(t_sdl sdl);

#endif
