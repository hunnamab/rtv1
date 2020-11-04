#ifndef TYPES_H
# define TYPES_H
# include <stdint.h>
//# include <SDL2/SDL.h> 
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
	const char 		*type;
}					t_light;

typedef	struct 		s_sphere
{
	t_point			center;
	float			radius;
}					t_sphere;

typedef struct		s_plane
{
	t_point			normal;
	t_point			point;
	float			d;
}					t_plane;

typedef	struct 		s_cylinder
{
	t_point			position;
	float			radius;
}					t_cylinder;

typedef	struct 		s_cone
{
	t_point			position;
}					t_cone;

typedef	struct		s_triangle
{
	t_point			*vertex;
	t_point			normal;
}					t_triangle;

typedef struct		s_camera
{
	t_point			position;
}					t_camera;

typedef	struct 		s_material
{
	t_color			color;
	float			specular;
}					t_material;

typedef	struct		s_object3d
{
	void			*data;
	const char		*tag;
	t_color			color;
	float			specular;
    float           (*get_normal)(struct s_scene *, int , int);
	float			(*intersect)(t_ray *, struct s_object3d *);
}					t_object;

typedef	struct 		s_scene
{
	t_object 		**objs;
	int 			obj_nmb;
	t_point			*normal_buf;
	t_material 		*material_buf;
	t_point 		*intersection_buf;
	t_ray 			*ray_buf;
	t_light 		**light;
	int 			light_nmb;
	t_camera		camera;
	t_point			*viewport;
	int				*index_buf;
	float 			*depth_buf;
}					t_scene;

#endif