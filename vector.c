/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:39:04 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/05 21:40:26 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point		vector_div_by_scalar(t_point *vector, double scalar)
{
	t_point result;

	result.x = vector->x / scalar;
	result.y = vector->y / scalar;
	result.z = vector->z / scalar;
	return (result);
}

double		vector_length(t_point *vector)
{
	double	dot;

	dot = vector_dot(vector, vector);
	return (sqrt(dot));
}

void		normalize_vector(t_point *v1)
{
	double q;

	q = sqrt(v1->x * v1->x + v1->y * v1->y + v1->z + v1->z);
	if (q != 0)
	{
		v1->x /= q;
		v1->y /= q;
		v1->z /= q;
	}
}

t_point		vector_cross(t_point *v1, t_point *v2)
{
	t_point result;

	result.x = v1->y * v2->z - v1->z * v2->y;
	result.y = v1->z * v2->x - v1->x * v2->z;
	result.z = v1->x * v2->y - v1->y * v2->x;
	return (result);
}

t_point		vector_add_scalar(const t_point *v1, const double scalar)
{
	t_point res;

	res.x = v1->x + scalar;
	res.y = v1->y + scalar;
	res.z = v1->z + scalar;
	return (res);
}
