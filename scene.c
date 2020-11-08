/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:21:11 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/08 18:10:22 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_deepth(t_scene *scene)
{
	double	**matrix;
	int		x;

	x = 0;
	scene->viewport = get_viewport(&scene->camera);
	scene->ray_buf = protected_malloc(sizeof(t_ray), (WID * HEI));
	get_rays_arr(scene);
	scene->depth_buf = protected_malloc(sizeof(double), WID * HEI);
	scene->index_buf = protected_malloc(sizeof(int), WID * HEI);
	matrix = get_rotation_matrix(&scene->camera.rotation);
	while (x < WID * HEI)
	{
		transform(&scene->ray_buf[x].dir, matrix, 1);
		x++;
	}
	matr_free(matrix, 4);
	get_closest_points(scene);
}

void	init_default(t_scene *scene)
{
	double	**matrix;
	int		x;

	x = 0;
	scene->viewport = get_viewport(&scene->camera);
	scene->ray_buf = protected_malloc(sizeof(t_ray), (WID * HEI));
	get_rays_arr(scene);
	scene->normal_buf = protected_malloc(sizeof(t_point), WID * HEI);
	scene->material_buf = protected_malloc(sizeof(t_material), WID * HEI);
	scene->intersection_buf = protected_malloc(sizeof(t_point), WID * HEI);
	scene->index_buf = protected_malloc(sizeof(int), WID * HEI);
	scene->depth_buf = protected_malloc(sizeof(double), WID * HEI);
	matrix = get_rotation_matrix(&scene->camera.rotation);
	while (x < WID * HEI)
	{
		transform(&scene->ray_buf[x].dir, matrix, 1);
		x++;
	}
	matr_free(matrix, 4);
	get_closest_points(scene);
	get_intersection_buf(scene);
	get_normal_buf(scene);
	get_material_buf(scene);
}

void	init_raycast(t_scene *scene)
{
	double	**matrix;
	int		x;

	x = 0;
	scene->viewport = get_viewport(&scene->camera);
	scene->ray_buf = protected_malloc(sizeof(t_ray), (WID * HEI));
	get_rays_arr(scene);
	scene->depth_buf = protected_malloc(sizeof(double), WID * HEI);
	scene->material_buf = protected_malloc(sizeof(t_material), WID * HEI);
	scene->index_buf = protected_malloc(sizeof(int), WID * HEI);
	scene->intersection_buf = protected_malloc(sizeof(t_point), WID * HEI);
	matrix = get_rotation_matrix(&scene->camera.rotation);
	while (x < WID * HEI)
	{
		transform(&scene->ray_buf[x].dir, matrix, 1);
		x++;
	}
	matr_free(matrix, 4);
	get_closest_points(scene);
	get_intersection_buf(scene);
	get_material_buf(scene);
}

void	init_scene(t_scene *scene)
{
	scene->init[0] = &init_default;
	scene->init[1] = &init_default;
	scene->init[2] = &init_deepth;
	scene->init[3] = &init_raycast;
	scene->draw[0] = &draw_scene;
	scene->draw[1] = &draw_normal_buf;
	scene->draw[2] = &draw_deepth_buf;
	scene->draw[3] = &draw_raycast;
	scene->clean[0] = &clean_scene_default;
	scene->clean[1] = &clean_scene_default;
	scene->clean[2] = &clean_scene_deepth;
	scene->clean[3] = &clean_scene_raycast;
	scene->init[scene->mode](scene);
}
