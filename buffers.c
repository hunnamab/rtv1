/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:38:29 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/09 11:17:50 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	get_rays_arr(t_scene *scene)
{
	int x;
	int y;
	int j;

	x = 0;
	y = 0;
	while (y < HEI)
	{
		while (x < WID)
		{
			j = y * WID + x;
			scene->ray_buf[j].start.x = scene->camera.position.x;
			scene->ray_buf[j].start.y = scene->camera.position.y;
			scene->ray_buf[j].start.z = scene->camera.position.z;
			scene->ray_buf[j].dir = vector_sub(&scene->viewport[j], \
												&scene->camera.position);
			x++;
		}
		x = 0;
		y++;
	}
}

void	get_closest_points(t_scene *scene)
{
	int		x;
	int		y;
	double	t;
	int		i;
	int		j;

	i = 0;
	t = 0;
	x = 0;
	y = 0;
	while (y < HEI)
	{
		while (x < WID)
		{
			j = y * WID + x;
			while (i < scene->obj_nmb)
			{
				t = scene->objs[i]->intersect(&scene->ray_buf[j], \
												scene->objs[i]);
				if (t)
					break ;
				i++;
			}
			scene->index_buf[j] = i;
			scene->depth_buf[j] = t;
			while (i < scene->obj_nmb)
			{
				t = scene->objs[i]->intersect(&scene->ray_buf[j], \
												scene->objs[i]);
				if (t < scene->depth_buf[j] && t != 0)
				{
					scene->depth_buf[j] = t;
					scene->index_buf[j] = i;
				}
				i++;
			}
			if (scene->depth_buf[j] < 1)
				scene->index_buf[j] = -1;
			x++;
			i = 0;
			t = 0;
		}
		x = 0;
		y++;
	}
}

void	get_intersection_buf(t_scene *scene)
{
	int x;
	int y;
	int i;

	x = 0;
	y = 0;
	while (y < HEI)
	{
		while (x < WID)
		{
			i = y * WID + x;
			if (scene->index_buf[i] != -1)
			{
				scene->intersection_buf[i] = vector_scale(scene->depth_buf[i], \
														&scene->ray_buf[i].dir);
				scene->intersection_buf[i] = \
									vector_add(&scene->intersection_buf[i], \
												&scene->ray_buf[i].start);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	get_normal_buf(t_scene *scene)
{
	int x;
	int y;
	int i;
	int j;

	j = 0;
	x = 0;
	y = 0;
	while (y < HEI)
	{
		while (x < WID)
		{
			i = y * WID + x;
			if (scene->index_buf[i] != -1)
			{
				j = scene->index_buf[i];
				scene->objs[j]->get_normal(scene, i, j);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	get_material_buf(t_scene *scene)
{
	int x;
	int y;
	int i;
	int j;

	j = 0;
	x = 0;
	y = 0;
	while (y < HEI)
	{
		while (x < WID)
		{
			i = y * WID + x;
			if (scene->index_buf[i] != -1)
			{
				j = scene->index_buf[i];
				copy_color(&scene->material_buf[i].color, \
							&scene->objs[j]->color);
				scene->material_buf[i].specular = scene->objs[j]->specular;
			}
			else
			{
				set_color_zero(&scene->material_buf[i].color);
				scene->material_buf[i].specular = -1;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
