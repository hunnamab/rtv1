/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:43 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/09 16:28:24 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	*get_parameters(char *name, char **description, t_scene *scene)
{
	t_object *obj;

	obj = NULL;
	if (ft_strequ(name, "sphere"))
	{
		printf("sphere\n");
		obj = get_sphere(description); // objects_parameters.c
	}
	else if (ft_strequ(name, "triangle"))
	{
		printf("triangle\n");
		obj = get_triangle(description);
	}
	else if (ft_strequ(name, "plane"))
	{
		printf("plane\n");
		obj = get_plane(description);
	}
	else if (ft_strequ(name, "cylinder"))
	{
		printf("cylinder\n");
		obj = get_cylinder(description);
	}
	else if (ft_strequ(name, "cone"))
	{
		printf("cone\n");
		obj = get_cone(description);
	}
	else if (ft_strequ(name, "light"))
	{
		printf("light\n");
		obj = get_light(description);
		scene->light_nmb += 1;
	}
	else
		output_error(4);
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
	if (scene[i] != '\n')
		output_error(6);
	if (!(descr_buf = ft_strsub(scene, start, len)))
		output_error(6);
	if (!(description = ft_strsplit(descr_buf, '\n')))
		output_error(6);
	ft_memdel(&descr_buf);
	return (description);
}

int			count_objects(int len, char *buf)
{
	int i;
	int obj_nmb;

	i = 0;
	obj_nmb = 0;
	while (i < len && buf[i])
	{
		if (buf[i] == '{')
			obj_nmb++;
		i++;
	}
	if (obj_nmb == 0)
		output_error(0);
	return (obj_nmb);
}

t_object	**get_objects(char *buf, t_scene *scene, int len)
{
	t_object	**objs;
	char		*obj_name;
	char		**obj_desc;
	int			start;
	int			n;
	int			i;
	int			camera;

	i = 0;
	n = 0;
	start = 0;
	camera = 0;
	scene->light_nmb = 0;
	scene->obj_nmb = 0;
	if (!brackets(buf))
		output_error(6);
	// выясняем кол-во объектов сцены
	scene->obj_nmb = count_objects(len, buf);
	// создаем массив структур для объектов
	objs = protected_malloc(sizeof(t_object *), scene->obj_nmb);
	while (i < len)
	{
		if (buf[i + 1] == '{' && n < scene->obj_nmb)
		{
			// записываем название объекта
			if (!(obj_name = ft_strsub(buf, start, (i - start))))
				output_error(6);
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
				add_camera(scene, obj_desc, &camera);
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
	if (scene->light_nmb == 0)
		output_error(1);
	if (camera != 1)
		output_error(2);
	scene->obj_nmb -= scene->light_nmb;
	if (scene->obj_nmb == 0)
		output_error(0);
	ft_memdel(&buf);
	return (objs);
}

t_object	**read_scene(int fd, t_scene *scene)
{
	int		ret;
	char	*buf;

	buf = protected_malloc(sizeof(char), 256000);
	ret = read(fd, buf, 64000);
	if (ret < 0)
		output_error(3);
	buf[ret] = '\0';
	printf("ret %d\n", ret);
	return (get_objects(buf, scene, ret));
}
