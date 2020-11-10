/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:37:58 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/09 12:46:52 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		*protected_malloc(unsigned int size, unsigned int nmb)
{
	void *result;

	if (!(result = malloc(size * nmb)))
	{
		ft_putstr("Malloc error, memory was nor allocated\n");
		exit(0);
	}
	return (result);
}

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
	if (t0 == t1 && t0 >= 0)
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
	viewport = protected_malloc(sizeof(t_point), (WID * HEI));
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
