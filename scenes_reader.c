/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:43 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/07 22:41:42 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		add_camera(t_scene *scene, char **description)
{
	printf("camera\n");
	scene->camera = get_camera(description);
	scene->obj_nmb--;
}

t_object	*get_parameters(char *name, char **description, t_scene *scene)
{
	t_object *obj;

	if (!ft_strcmp(name, "sphere"))
	{
		printf("sphere\n");
		obj = get_sphere(description); // objects_parameters.c
	}
	else if (!ft_strcmp(name, "triangle"))
	{
		printf("triangle\n");
		obj = get_triangle(description);
	}
	else if (!ft_strcmp(name, "plane"))
	{
		printf("plane\n");
		obj = get_plane(description);
	}
	else if (!ft_strcmp(name, "cylinder"))
	{
		printf("cylinder\n");
		obj = get_cylinder(description);
	}
	else if (!ft_strcmp(name, "cone"))
	{
		printf("cone\n");
		obj = get_cone(description);
	}
	else if (!ft_strcmp(name, "light"))
	{
		printf("light\n");
		obj = get_light(description);
		scene->light_nmb += 1;
	}
	else
		return (NULL);
	return (obj);
}

char		**get_description(char *scene, int i)
{
	char	*descr_buf;
	char	**description;
	int		len;
	int		start;

	len = 0;
	start = i;
	while (scene[i + 1] != '}')
	{
		i++;
		len++;
	}
	descr_buf = ft_strsub(scene, start, len);
	description = ft_strsplit(descr_buf, '\n');
	ft_memdel(&descr_buf);
	return (description);
}

t_object	**get_objects(char *buf, t_scene *scene)
{
	t_object	**objs;
	char		*obj_name;
	char		**obj_desc;
	int			start;
	int			n;
	int			i;
	int			len;

	i = 0;
	scene->light_nmb = 0;
	len = ft_strlen(buf);
	// выясняем кол-во объектов сцены
	while (i < len)
	{
		if (buf[i] == '{')
			scene->obj_nmb++;
		i++;
	}
	// создаем массив структур для объектов
	if (!(objs = malloc(sizeof(t_object *) * scene->obj_nmb)))
	{
		printf("cannot allocate memory for objs\n");
		return (NULL);
	}
	i = 0;
	n = 0;
	start = 0;
	while (i < len)
	{
		if (buf[i + 1] == '{' && n < scene->obj_nmb)
		{
			// записываем название объекта
			obj_name = ft_strsub(buf, start, (i - start));
			// записываем описание объекта
			obj_desc = get_description(buf, i + 3);
			if (!(ft_strequ(obj_name, "camera")))
			{
				// создаем объект и получаем его характеристики
				objs[n] = get_parameters(obj_name, obj_desc, scene);
				// плюсуем индекс массива, если объект не камера
				n++;
			}
			else if ((ft_strequ(obj_name, "camera")))
				add_camera(scene, obj_desc);
			// освобождаем строки
			ft_memdel(&obj_name);
			ft_memdel_double(obj_desc);
			// переходим к описанию следующего объекта
			while (buf[i] != '}')
				i++;
			start = i + 3;
		}
		i++;
	}
	scene->obj_nmb -= scene->light_nmb;
	return (objs);
}

t_object	**read_scene(int fd, t_scene *scene)
{
	int		ret;
	char	buf[64000];

	ret = read(fd, buf, 64000);
	buf[ret] = '\0';
	printf("ret %d\n", ret);
	return (get_objects(buf, scene));
}
