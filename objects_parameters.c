/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_parameters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:22 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/08 18:15:43 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*get_coordinates(char *description)
{
	char	*coordinates;
	int		i;
	int		len;

	if (!description)
		output_error(5);
	i = 0;
	len = ft_strlen(description);
	while (!(ft_isdigit(description[i])) && description[i] != '-')
	{
		if (description[i + 1] == '\0')
			output_error(5);
		i++;
	}
	if (!(coordinates = ft_strsub(description, i, len - i)))
		output_error(5);
	return (coordinates);
}

t_color		get_color(char *description)
{
	char	*coord_buf;
	char	**coordinates;
	t_color	color;

	if (!description)
		output_error(5);
	coord_buf = get_coordinates(description);
	if (!(coordinates = ft_strsplit(coord_buf, ',')))
		output_error(5);
	free(coord_buf);
	if (!coordinates[0] || !coordinates[1] || !coordinates[2] || !coordinates[3])
		output_error(5);
	color.red = ft_atoi(coordinates[0]);
	color.green = ft_atoi(coordinates[1]);
	color.blue = ft_atoi(coordinates[2]);
	color.alpha = ft_atoi(coordinates[3]);
	ft_memdel_double(coordinates);
	return (color);
}

t_point		get_points(char *description)
{
	char	*coord_buf;
	char	**coordinates;
	t_point	points;

	if (!description)
		output_error(5);
	printf("description in get_points = |%s|\n", description);
	coord_buf = get_coordinates(description);
	if (!(coordinates = ft_strsplit(coord_buf, ',')))
		output_error(5);
	free(coord_buf);
	if (!coordinates[0] || !coordinates[1] || !coordinates[2])
		output_error(5);
	points.x = ftoi(ft_strtrim(coordinates[0]));
	printf("x = %f\n", points.x);
	points.y = ftoi(ft_strtrim(coordinates[1]));
	printf("y = %f\n", points.y);
	points.z = ftoi(ft_strtrim(coordinates[2]));
	printf("z = %f\n", points.z);
	ft_memdel_double(coordinates);
	return (points);
}

t_object	*get_sphere(char **description)
{
	t_object	*sphere;
	t_point		center;
	double		radius;
	double		specular;
	t_color		color;
	t_point		buf;
	double		rotation[3];

	center = get_points(description[0]);
	radius = ftoi(get_coordinates(description[1]));
	buf = get_points(description[2]);
	rotation[0] = buf.x;
	rotation[1] = buf.y;
	rotation[2] = buf.z;
	color = get_color(description[3]);
	specular = ftoi(get_coordinates(description[4]));
	sphere = new_sphere(center, radius, specular, color, rotation);
	return (sphere);
}

t_object	*get_cylinder(char **description)
{
	t_object	*cylinder;
	t_point		position;
	t_point		vec;
	double		radius;
	double		specular;
	t_color		color;
	t_point		buf;
	double		rotation[3];

	position = get_points(description[0]);
	radius = ftoi(get_coordinates(description[1]));
	vec = get_points(description[2]);
	buf = get_points(description[3]);
	rotation[0] = buf.x;
	rotation[1] = buf.y;
	rotation[2] = buf.z;
	color = get_color(description[4]);
	specular = ftoi(get_coordinates(description[5]));
	cylinder = new_cylinder(position, vec, radius, specular, color, rotation);
	return (cylinder);
}

t_object	*get_cone(char **description)
{
	t_object	*cone;
	t_point		position;
	t_point		vec;
	double		specular;
	t_color		color;
	t_point		buf;
	double		rotation[3];
	double		angle;

	position = get_points(description[0]);
	vec = get_points(description[1]);
	angle = ftoi(get_coordinates(description[2]));
	printf("angle = %f\n", angle);
	buf = get_points(description[3]);
	rotation[0] = buf.x;
	rotation[1] = buf.y;
	rotation[2] = buf.z;
	color = get_color(description[4]);
	specular = ftoi(get_coordinates(description[5]));
	cone = new_cone(position, vec, specular, color, rotation, angle);
	return (cone);
}

t_object	*get_triangle(char **description)
{
	t_object	*triangle;
	t_point		vertex[3];
	double		specular;
	t_color		color;
	t_point		buf;
	double		rotation[3];

	vertex[0] = get_points(description[0]);
	vertex[1] = get_points(description[1]);
	vertex[2] = get_points(description[2]);
	buf = get_points(description[3]);
	rotation[0] = buf.x;
	rotation[1] = buf.y;
	rotation[2] = buf.z;
	color = get_color(description[4]);
	specular = ftoi(get_coordinates(description[5]));
	triangle = new_triangle(vertex, specular, color, rotation);
	return (triangle);
}

t_object	*get_plane(char **description)
{
	t_object	*plane;
	t_point		point;
	t_point		normal;
	t_point		buf;
	double		specular;
	t_color		color;
	double		rotation[3];

	point = get_points(description[0]);
	normal = get_points(description[1]);
	buf = get_points(description[2]);
	rotation[0] = buf.x;
	rotation[1] = buf.y;
	rotation[2] = buf.z;
	color = get_color(description[3]);
	specular = ftoi(get_coordinates(description[4]));
	plane = new_plane(point, normal, specular, color, rotation);
	return (plane);
}

char		*get_light_type(char *description)
{
	char	*type;
	int		i;
	int		len;

	if (!description)
		output_error(5);
	i = 0;
	len = ft_strlen(description);
	while (description[i] != ':' && description != '\0')
		i++;
	i++;
	type = ft_strsub(description, i, len - i);
	return (ft_strtrim(type));
}

t_object	*get_light(char **description)
{
	t_object	*light;
	t_point		position;
	t_point		direction;
	char		*type;

	light = protected_malloc(sizeof(t_object), 1);
	type = get_light_type(description[0]);
	printf("light type = |%s|\n", type);
	position.x = 0.0;
	position.y = 0.0;
	position.z = 0.0;
	direction.x = 0.0;
	direction.y = 0.0;
	direction.z = 0.0;
	if (ft_strequ(type, "point"))
		position = get_points(description[1]);
	else if (ft_strequ(type, "directional"))
		direction = get_points(description[1]);
	else if (!(ft_strequ(type, "ambient")))
		output_error(5);
	light->data = (void *)new_light(position, direction, (const char *)type);
	light->tag = ft_strdup("light");
	free(type);
	return (light);
}

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
