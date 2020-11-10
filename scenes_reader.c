/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:43 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/10 14:19:09 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char	**get_description(char *scene, int i)
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
	ft_memdel((void **)&descr_buf);
	return (description);
}

static int	count_objects(int len, char *buf)
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

static void	split_objects(int len, t_scene *scene, char *buf)
{
	char	*obj_name;
	int		i;
	int		start;
	int		camera;

	i = 0;
	start = 0;
	camera = 0;
	while (i < len)
	{
		if (buf[i + 1] == '{' && scene->obj_nmb > 0)
		{
			if (!(obj_name = ft_strsub(buf, start, (i - start))))
				output_error(6);
			if (ft_strequ(obj_name, "light"))
				scene->light_nmb++;
			if (ft_strequ(obj_name, "camera"))
				camera++;
			ft_memdel((void **)&obj_name);
			while (buf[i] != '}')
				i++;
			start = i + 3;
			scene->obj_nmb--;
		}
		i++;
	}
	scene->obj_nmb -= scene->light_nmb - camera;
	if (scene->obj_nmb < 1 || scene->light_nmb < 1 || camera != 1)
		output_error(0);
}

static void scene_description()
{

}

static void	get_objects(char *buf, t_scene *scene, int len)
{
	char		*obj_name;
	char		**obj_desc;
	int			start;
	int			n;
	int			m;
	int			i;

	i = 0;
	n = 0;
	m = 0;
	start = 0;
	if (!brackets(buf))
		output_error(6);
	scene->obj_nmb = count_objects(len, buf); // выясняем кол-во объектов сцены
	split_objects(len, scene, buf);
	scene->objs = protected_malloc(sizeof(t_object *), scene->obj_nmb); // создаем массив структур для объектов
	scene->light = protected_malloc(sizeof(t_light *), scene->light_nmb);
	while (i < len)
	{
		if (buf[i + 1] == '{')
		{
			obj_name = ft_strsub(buf, start, (i - start)); // записываем название объекта
			obj_desc = get_description(buf, i + 3); // записываем описание объекта
			if (!(ft_strequ(obj_name, "camera")) && \
				!(ft_strequ(obj_name, "light")) && n < scene->obj_nmb)
			{
				scene->objs[n] = get_parameters(obj_name, obj_desc); // создаем объект и получаем его характеристики
				n++; // плюсуем индекс массива, если объект не камера
			}
			else if ((ft_strequ(obj_name, "camera")))
				scene->camera = get_camera(obj_desc);
			else if ((ft_strequ(obj_name, "light")) && m < scene->light_nmb)
			{
				scene->light[m] = get_light(obj_desc);
				m++;
			}
			ft_memdel((void **)&obj_name); // освобождаем строки
			ft_memdel_double((void **)obj_desc);
			while (buf[i] != '}') // переходим к описанию следующего объекта
				i++;
			start = i + 3;
		}
		i++;
	}
	ft_memdel((void **)&buf);
}

void		read_scene(int fd, t_scene *scene)
{
	int		ret;
	char	*buf;

	buf = protected_malloc(sizeof(char), 256000);
	ret = read(fd, buf, 64000);
	if (ret < 0)
		output_error(3);
	buf[ret] = '\0';
	scene->obj_nmb = 0;
	scene->light_nmb = 0;
	get_objects(buf, scene, ret);
}
