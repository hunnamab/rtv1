/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:38:51 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/08 18:03:19 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light		**get_light_structures(int light_nmb, t_object **buf)
{
	int		i;
	int		j;
	t_light	**light;

	light = protected_malloc(sizeof(t_light *), light_nmb);
	i = 0;
	j = 0;
	while (j < light_nmb)
	{
		if (!(ft_strequ(buf[i]->tag, "light")))
			i++;
		else
		{
			light[j] = (t_light *)buf[i]->data;
			printf("light type = %s\n", light[j]->type);
			i++;
			j++;
		}
	}
	return (light);
}

t_object	**get_objects_structures(int obj_nmb, t_object **buf)
{
	int			i;
	int			j;
	t_object	**objs;

	objs = protected_malloc(sizeof(t_object *) , obj_nmb);
	i = 0;
	j = 0;
	while (j < obj_nmb)
	{
		if ((ft_strequ(buf[i]->tag, "light")))
			i++;
		else
		{
			objs[j] = buf[i];
			printf("object tag = %s\n", objs[j]->tag);
			i++;
	 		j++;
	 	}
	}
	return (objs);
}
