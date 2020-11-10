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

void		clear_default(t_object *obj)
{
	free(obj->data);
	free(obj);
}

void	clean_scene(t_scene *scene)
{
	int i;

	i = 0;
	ft_memdel(&scene->normal_buf);
	ft_memdel(&scene->material_buf);
	ft_memdel(&scene->intersection_buf);
	ft_memdel(&scene->ray_buf);
	ft_memdel(&scene->viewport);
	ft_memdel(&scene->index_buf);
	ft_memdel(&scene->depth_buf);
	while (i < scene->obj_nmb)
	{
		scene->objs[i]->clear_obj(scene->objs[i]);
		i++;
	}
	i = 0;
	while (i < scene->light_nmb)
	{
		ft_memdel(&scene->light[i]->type);
		ft_memdel(&scene->light[i]);
		i++;
	}
	free(scene->light);
	free(scene->objs);
	ft_memdel(&scene);
}
