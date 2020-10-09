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
# include "matrix_lib/matrix.h"

# define WID 1280
# define HEI 720

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

typedef	struct		s_object3d
{
	void			*data;
	const char		*tag;
	t_color			color;
	float			specular;
	int		(*intersect)(t_ray *, struct s_object3d *, t_point *, float *t);
}					t_object;

// scenes_reader.c
t_object	**read_scene(int fd, int *obj_nmb, int *light_nmb);
// settings.c
void 		sphere_settings(t_sphere *s, t_ray *r);
// draw.c
void 		draw_objects(t_sdl *sdl, t_object **objs, int obj_nmb, t_light **light, int light_nmb);
// light.c
t_color     reflection_color(t_point *P, t_color *normal, t_point *V, t_object *o, t_light **light, int light_nmb);
t_light     *new_light(t_point position, t_point direction, const char *type);
// vector.c
t_point 	vector_add(const t_point *v1, const t_point *v2);
t_point 	vector_scale(float c, t_point *v);
t_point 	vector_sub(t_point *v1, t_point *v2);
float 		vector_dot(t_point *v1, t_point *v2);
t_point  	vector_cross(t_point *v1, t_point *v2);
float   	vector_length(t_point *vector);
t_point     vector_div_by_scalar(t_point *vector, float scalar);
t_point     vector_sub_by_scalar(t_point *vector, float scalar);
void  		normalize_vector(t_point *v1);
// utils.c
t_point		get_point(float x, float y, float z);
// sphere.c
int intersect_ray_sphere(t_ray *r, t_object *object, t_point *normal, float *t);
t_object	*new_sphere(t_point center, float radius, float specular, t_color color);
// triangle.c
int intersect_ray_triangle(t_ray *r, t_object *object, t_point *normal, float *t);
t_object 	*new_triangle(t_point *vertex, double specular, t_color color);
// plane.c
int intersect_ray_plane(t_ray *r, t_object *object, t_point *normal, float *t);
t_object 	*new_plane(t_point point, t_point normal, float specular, t_color color);
// cylinder.c
int intersect_ray_cylinder(t_ray *r, t_object *object, t_point *normal, float *t);
t_object	*new_cylinder(t_point position, float radius, float specular, t_color color);
// cone.c
int intersect_ray_cone(t_ray *r, t_object *object, t_point *normal, float *t);
t_object	*new_cone(t_point position, float specular, t_color color);
// ftoi.c
float   	ftoi(char *str);
// objects_parameters.c
t_object	*get_sphere(char **description);
t_object	*get_triangle(char **description);
t_object 	*get_plane(char **description);
t_object 	*get_cylinder(char **description);
t_object 	*get_cone(char **description);
t_object 	*get_light(char **description);
// translate.c
float		**get_transform_matrix(float *angle, float *move, float *scale);
float		*get_three_floats(float x, float y, float z);
void		transform(t_point *point, float **matrix, float *coord_matrix, int point_nmb);
// get_structures.c
t_object 	**get_objects_structures(int obj_nmb, t_object **buf);
t_light 	**get_light_structures(int light_nmb, t_object **buf);

#endif
