/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_parameters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:39:22 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/09 12:01:57 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
