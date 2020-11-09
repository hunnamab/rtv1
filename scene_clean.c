/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:32:12 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/09 12:14:22 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	clean_scene_default(t_scene *scene)
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
	while (i < scene->light_nmb)
	{
		free(scene->light[i]);
		i++;
	}
	free(scene->light);
	free(scene->objs);
}

void	clean_scene_deepth(t_scene *scene)
{
	int i;

	i = 0;
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
	while (i < scene->light_nmb)
	{
		free(scene->light[i]);
		i++;
	}
	free(scene->light);
	free(scene->objs);
}

void	clean_scene_raycast(t_scene *scene)
{
	int i;

	i = 0;
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
	while (i < scene->light_nmb)
	{
		free(scene->light[i]);
		i++;
	}
	free(scene->light);
	free(scene->objs);
}
