/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:23:24 by pmetron           #+#    #+#             */
/*   Updated: 2020/11/09 15:28:30 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light		*new_light(t_point position, t_point direction, const char *type, double intensity)
{
	t_light *new_light;

	new_light = protected_malloc(sizeof(t_light), 1);
	new_light->type = ft_strcpy_alloc(new_light->type, type);
	new_light->intensity = intensity;
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

int			in_shadow(t_scene *scene, int index, t_point l, t_point l_pos)
{
	t_ray	ray;
	int		i;
	double	t;
	double	buf;
	double dist;
	t_point buf2;
	i = 0;
	
	ray.dir = l;
	ray.start = scene->intersection_buf[index];
	buf2 = vector_scale(&ray.dir, 0.0001);
	ray.start = vector_add(&ray.start, &buf2);
	buf2 = vector_sub(&l_pos, &ray.start);
	dist = vector_length(&buf2);
	buf = 0;
	t = dist;
	while (i < scene->obj_nmb)
	{
		buf = scene->objs[i]->intersect(&ray, scene->objs[i]);
		if (t > buf && buf > 0.0001)
			t = buf;
		i++;
	}
	if (t < dist && t > 0.0001)
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
	t_point lb;

	lb = vector_div_by_scalar(l, vector_length(l));
	i = 0;
	n_dot_l = vector_dot(&scene->normal_buf[index], &lb);
	r = vector_scale(&scene->normal_buf[index], 2.0);
	r = vector_scale(&r, n_dot_l);
	r = vector_sub(&r, &lb);
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
	t_point lb;
	
	j = -1;
	i = 0;
	while (++j < scene->light_nmb)
	{
		if (ft_strequ(scene->light[j]->type, "ambient"))
			i += 0.2;
		else
		{
			l = get_light_vec(scene, index, &i, j);
			lb = vector_div_by_scalar(&l, vector_length(&l));
			n_dot_l = vector_dot(&scene->normal_buf[index], &l);
			if (!(in_shadow(scene, index, lb, scene->light[j]->position)) && n_dot_l > 0)
			{
				if (scene->material_buf[index].specular != -1)
					i += get_specular(scene, index, j, &l);
				i += (scene->light[j]->intensity * n_dot_l) / vector_length(&l);
			}
		}
	}
	i = i > 1 ? 1 : i;
	return (color_mul_by_scalar(&scene->material_buf[index].color, i));
}
