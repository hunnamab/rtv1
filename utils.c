/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:37:58 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/05 21:38:40 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point		get_point(double x, double y, double z)
{
	t_point result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

void		copy_point(t_point *dst, t_point *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

double		choose_t(double t0, double t1)
{
	double result;

	result = 0;
	if ((t1 < t0 && t1 > 0) || (t0 < 0 && t1 >= 0))
		result = t1;
	if ((t0 < t1 && t0 > 0) || (t1 < 0 && t0 >= 0))
		result = t0;
	if (t0 == t1 && t0 > 0)
		result = t0;
	return (result);
}

t_point		*get_viewport(t_camera *camera)
{
	int		x;
	int		y;
	t_point	*viewport;
	double	k;

	k = (double)WID / (double)HEI;
	viewport = malloc(sizeof(t_point) * (WID * HEI));
	x = 0;
	y = 0;
	while (y < HEI)
	{
		while (x < WID)
		{
			viewport[y * WID + x].y = -(y - (double)HEI / 2) *\
			(1 / (double)HEI) + camera->position.y;
			viewport[y * WID + x].x = (x - (double)WID / 2) *\
			(k / (double)WID) + camera->position.x;
			viewport[y * WID + x].z = camera->position.z + 1;
			x++;
		}
		x = 0;
		y++;
	}
	return (viewport);
}
