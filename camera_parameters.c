/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:00:26 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/09 12:34:17 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_camera	get_camera(char **description)
{
	t_camera	camera;
	t_point		buf;

	camera.position = get_points(description[0]);
	buf = get_points(description[1]);
	camera.rotation[0] = buf.x;
	camera.rotation[1] = buf.y;
	camera.rotation[2] = buf.z;
	return (camera);
}

void		add_camera(t_scene *scene, char **description, int *camera)
{
	int nmb;

	nmb = 0;
	printf("camera\n");
	scene->camera = get_camera(description);
	scene->obj_nmb--;
	nmb = *camera + 1;
	*camera = nmb;
}
