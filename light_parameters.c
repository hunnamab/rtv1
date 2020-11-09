/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 11:58:35 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/09 16:22:19 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*get_light_type(char *description)
{
	char	*type;
	char	*buf;
	int		i;
	int		len;

	if (!description)
		output_error(5);
	i = 0;
	len = ft_strlen(description);
	while (description[i] != ':' && description[i] != '\0')
		i++;
	i++;
	type = ft_strsub(description, i, len - i);
	buf = ft_strtrim(type);
	free(type);
	return (buf);
}

t_light		*get_light(char **description)
{
	t_light		*light;
	t_point		position;
	t_point		direction;
	char		*type;

	light = NULL;
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
	light = new_light(position, direction, type);
	free(type);
	return (light);
}
