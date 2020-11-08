/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:21:11 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/08 17:36:49 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
