/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:21:11 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/07 22:15:28 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	clear_scene(t_scene *scene)
{
	int i;

	i = 0;
	free(scene->normal_buf);
	free(scene->material_buf);
	free(scene->intersection_buf);
	free(scene->ray_buf);
	free(scene->viewport);
	free(scene->index_buf);
	free(scene->depth_buf);
	while (i < scene->obj_nmb)
	{
		scene->objs[i]->clear_obj(scene->objs[i]);
		i++;
	}
	i = 0;
	while(i < scene->light_nmb)
	{
		free(scene->light[i]);
		i++;
	}
	free(scene->light);
	free(scene->objs);
}

void	buffer_recalc(t_scene *scene)
{
	get_rays_arr(&scene);
	get_closest_points(scene);
	get_intersection_buf(scene);
	get_normal_buf(scene);
	get_material_buf(scene);
}

void	init_scene(t_scene *scene)
{
	double	**matrix;
	int		x;

	x = 0;
	scene->viewport = get_viewport(&scene->camera);
	scene->ray_buf = malloc(sizeof(t_ray) * (WID * HEI));
	get_rays_arr(scene);
	scene->normal_buf = malloc(sizeof(t_point) * WID * HEI);
	scene->material_buf = malloc(sizeof(t_material) * WID * HEI);
	scene->intersection_buf = malloc(sizeof(t_point) * WID * HEI);
	scene->index_buf = malloc(sizeof(int) * WID * HEI);
	scene->depth_buf = malloc(sizeof(double) * WID * HEI);
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
