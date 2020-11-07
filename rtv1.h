/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:34 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/07 19:49:44 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "matrix_lib/matrix.h"
# include "types.h"

# define WID 640
# define HEI 640

// scenes_reader.c
t_object	**read_scene(int fd, t_scene *scene);
// settings.c
void 		sphere_settings(t_sphere *s, t_ray *r);
// draw.c
void    	draw_scene(t_sdl *sdl, t_scene *scene);
void    	draw_normal_buf(t_sdl *sdl, t_scene *scene);
// light.c
t_color     reflection_color(t_scene *scene, int index);
t_light     *new_light(t_point position, t_point direction, const char *type);
t_point     get_light_vec(t_scene *scene, int index, double *i, int j);
double       get_specular(t_scene *scene, int index, int j, t_point *L);
int         in_shadow(t_scene *scene, int index, t_point *L);
// vector.c
t_point 	vector_add(const t_point *v1, const t_point *v2);
t_point 	vector_scale(double c, t_point *v);
t_point 	vector_sub(t_point *v1, t_point *v2);
double 		vector_dot(t_point *v1, t_point *v2);
t_point  	vector_cross(t_point *v1, t_point *v2);
double   	vector_length(t_point *vector);
t_point     vector_div_by_scalar(t_point *vector, double scalar);
t_point     vector_sub_by_scalar(t_point *vector, double scalar);
void  		normalize_vector(t_point *v1);
t_point     vector_add_scalar(const t_point *v1, const double scalar);
// utils.c
t_point		get_point(double x, double y, double z);
t_point     *get_viewport(t_camera *camera);
void        copy_point(t_point *dst, t_point *src);
double      choose_t(double t0, double t1);
void		clear_default(t_object *obj);
//color.c
void        copy_color(t_color *dst, t_color *src);
t_color     set_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
void        set_color_zero(t_color *color);
t_color     color_mul_by_scalar(t_color *color, double scalar);
// sphere.c
double 		intersect_ray_sphere(t_ray *r, t_object *object);
t_object	*new_sphere(t_point center, double radius, double specular, t_color color);
// triangle.c
double 		intersect_ray_triangle(t_ray *r, t_object *object);
t_object 	*new_triangle(t_point *vertex, double specular, t_color color);
void		clear_triangle(t_object *obj);
// plane.c
double 		intersect_ray_plane(t_ray *r, t_object *object, t_point *normal);
t_object 	*new_plane(t_point point, t_point normal, double specular, t_color color);
// cylinder.c
double      intersect_ray_cylinder(t_ray *r, t_object *object);
t_object	*new_cylinder(t_point position, t_point vec, double radius, double specular, t_color color);
// cone.c
double      intersect_ray_cone(t_ray *r, t_object *object);
t_object    *new_cone(t_point position, t_point vec, double specular, t_color color);
// ftoi.c
double   	ftoi(char *str);
// objects_parameters.c
t_object	*get_sphere(char **description);
t_object	*get_triangle(char **description);
t_object 	*get_plane(char **description);
t_object 	*get_cylinder(char **description);
t_object 	*get_cone(char **description);
t_object 	*get_light(char **description);
t_camera	get_camera(char **description);
// transform.c
double		**get_transform_matrix(double *angle, double *move, double *scale);
double	    **get_rotation_matrix(double *angle);
double		*get_three_doubles(double x, double y, double z);
void		transform(t_point *point, double **matrix, int point_nmb);
// transform_matrix.c
double	    **get_translate_matrix(double *move);
double	    **get_scale_matrix(double *scale);
double	    **rotate_x(double x);
double	    **rotate_z(double z);
double	    **rotate_y(double y);
// get_structures.c
t_object 	**get_objects_structures(int obj_nmb, t_object **buf);
t_light 	**get_light_structures(int light_nmb, t_object **buf);
//buffers.c
void        get_rays_arr(t_scene *scene);
void     	get_buffers(t_scene *scene);
void    	get_normal_buf(t_scene *scene);
void    	get_intersection_buf(t_scene *scene);
void     	get_closest_points(t_scene *scene);
void    	get_material_buf(t_scene *scene);
//normal.c
void        get_sphere_normal(t_scene *scene, int index, int obj_num);
void        get_plane_normal(t_scene *scene, int index, int obj_num);
void        get_triangle_normal(t_scene *scene, int index, int obj_num);
void        get_cone_normal(t_scene *scene, int index, int obj_num);
void        get_cylinder_normal(t_scene *scene, int index, int obj_num);
//scene.c
void        init_scene(t_scene *scene);
void        clear_scene(t_scene *scene);
//keyboard.c
void        camera_left(t_scene *scene);
int         keyboard(t_sdl *sdl, t_scene *scene);
void        camera_up(t_scene *scene);
void        camera_right(t_scene *scene);
void        camera_down(t_scene *scene);

#endif
