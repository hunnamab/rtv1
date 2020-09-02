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

# define WID 800
# define HEI 600

typedef struct 		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Event		event;
}                	t_sdl;

typedef struct		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef	struct 		s_color
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	uint8_t			alpha;
}					t_color;

typedef	struct 		s_sphere
{
	t_point			center;
	int16_t			radius;
	t_color			color;
	int				material;
}					t_sphere;

typedef struct		s_ray
{
	t_point			start;
	t_point			dir;
}					t_ray;

typedef struct		s_light
{
	t_point			pos;
	t_color			intensity;
}					t_light;

typedef struct		s_material
{
	t_color			diffuse;
	float			reflection;
}					t_material;

void	julia(t_sdl sdl);
void 	sphere_settings(t_sphere *s, t_ray *r);
int		intersect_ray_sphere(t_ray *r, t_sphere *s, float *t);
void 	draw_sphere(t_sdl *sdl);

#endif
