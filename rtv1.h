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

typedef struct		s_ray
{
	t_point			start;
	t_point			dir;
}					t_ray;

typedef	struct 		s_color
{
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	uint8_t			alpha;
}					t_color;

typedef	struct		s_light
{
	float			intensity;
	t_point			position;
	t_point			direction;
}					t_light;

typedef	struct 		s_sphere
{
	t_point			center;
	float			radius;
}					t_sphere;

typedef	struct		s_triangle
{
	t_point			*vertex;
}					t_triangle;

typedef	struct		s_object3d
{
	void			*data;
	const char		*tag;
	t_color			color;
	double			specular;
	int				(*intersect)(t_ray *, struct s_object3d *, t_color *);
}					t_object;

// scenes_reader.c
void		read_scene(int fd);
// settings.c
void 		sphere_settings(t_sphere *s, t_ray *r);
// draw.c
void 		draw_sphere(t_sdl *sdl);
// vector.c
t_point 	vector_add(t_point *v1, t_point *v2);
t_point 	vector_scale(float c, t_point *v);
t_point 	vector_sub(t_point *v1, t_point *v2);
float 		vector_dot(t_point *v1, t_point *v2);
t_point  	vector_cross(t_point *v1, t_point *v2);
float   	vector_length(t_point *vector);
t_point     vector_div_by_scalar(t_point *vector, float scalar);
t_point     vector_sub_by_scalar(t_point *vector, float scalar);
// sphere.c
int 		intersect_ray_sphere(t_ray *r, t_object *object, t_color *reflected_color);
// utils.c
t_point		get_point(float x, float y, float z);
t_color     reflection_color(t_point *P, t_point *N, t_point *V, t_object *o);
// triangle.c
int intersect_ray_triangle(t_ray *r, t_object *object, t_color *reflected_color);
// new_objects.c
t_object 	*new_triangle(t_point v1, t_point v2, t_point v3);
t_object	*new_sphere(t_point center, int16_t radius);
// ftoi.c
float   	ftoi(char *str);
// objects_parameters.c
t_object *get_sphere(char *description);

#endif
