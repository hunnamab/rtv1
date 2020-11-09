/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:58:35 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/09 12:03:34 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
