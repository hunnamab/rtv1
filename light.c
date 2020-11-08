/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:23:24 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/08 18:05:35 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light		*new_light(t_point position, t_point direction, const char *type)
{
	t_light *new_light;

	new_light = protected_malloc(sizeof(t_light), 1);
	new_light->type = ft_strcpy_alloc(new_light->type, type);
	if (ft_strequ(new_light->type, "point"))
		new_light->intensity = 0.2;
	else
		new_light->intensity = 0.2;
	new_light->position = position;
	new_light->direction = direction;
	return (new_light);
}

t_point		get_light_vec(t_scene *scene, int index, double *i, int j)
{
	t_point light_vec;

	light_vec = get_point(0, 0, 0);
	if (ft_strequ(scene->light[j]->type, "point"))
		light_vec = vector_sub(&scene->light[j]->position, \
		&scene->intersection_buf[index]);
	if (ft_strequ(scene->light[j]->type, "directional"))
		light_vec = scene->light[j]->direction;
	return (light_vec);
}

int			in_shadow(t_scene *scene, int index, t_point *l)
{
	t_ray	ray;
	int		i;
	double	t;
	double	buf;

	i = 0;
	ray.start = scene->intersection_buf[index];
	ray.dir = *l;
	buf = 0;
	t = 2;
	while (i < scene->obj_nmb)
	{
		buf = scene->objs[i]->intersect(&ray, scene->objs[i]);
		if (t > buf && buf > 0.00001)
			t = buf;
		i++;
	}
	if (t < 1 && t > 0.00001)
		return (1);
	return (0);
}

double		get_specular(t_scene *scene, int index, int j, t_point *l)
{
	double		r_dot_v;
	t_point		r;
	t_point		d;
	double		i;
	double		n_dot_l;

	i = 0;
	n_dot_l = vector_dot(&scene->normal_buf[index], l);
	r = vector_scale(2.0, &scene->normal_buf[index]);
	r = vector_scale(n_dot_l, &r);
	r = vector_sub(&r, l);
	d.x = -scene->ray_buf[index].dir.x;
	d.y = -scene->ray_buf[index].dir.y;
	d.z = -scene->ray_buf[index].dir.z;
	r_dot_v = vector_dot(&r, &d);
	if (r_dot_v > 0)
		i += scene->light[j]->intensity * pow((double)r_dot_v / \
		(vector_length(&r) * vector_length(&d)), \
		scene->material_buf[index].specular);
	return (i);
}

t_color		reflection_color(t_scene *scene, int index)
{
	double	i;
	t_point	l;
	double	n_dot_l;
	int		j;

	j = -1;
	i = 0;
	while (++j < scene->light_nmb)
	{
		if (ft_strequ(scene->light[j]->type, "ambient"))
			i += 0.2;
		else
		{
			l = get_light_vec(scene, index, &i, j);
			n_dot_l = vector_dot(&scene->normal_buf[index], &l);
			if (!in_shadow(scene, index, &l) && n_dot_l > 0)
			{
				i += (scene->light[j]->intensity * n_dot_l) / vector_length(&l);
				if (scene->material_buf[index].specular != -1)
					i += get_specular(scene, index, j, &l);
			}
		}
	}
	i = i > 1 ? 1 : i;
	return (color_mul_by_scalar(&scene->material_buf[index].color, i));
}
