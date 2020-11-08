/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brackets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunnamab <hunnamab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 20:33:44 by hunnamab          #+#    #+#             */
/*   Updated: 2020/11/08 20:33:46 by hunnamab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int matching(char b1, char b2)
{
	if (b1 == '(' && b2 == ')')
		return (1);
	if (b1 == '[' && b2 == ']')
		return (1);
	if (b1 == '{' && b2 == '}')
		return (1);
	return (0);
}

int brackets(char *str)
{
	int		i;
	int		top;
	char	stack[64000];

	i = 0;
	top = -1;
	while (str[i] != '\0')
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			top++;
			stack[top] = str[i];
		}
		if (str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			if (!stack[top])
				return (0);
			else if (!matching(stack[top], str[i]))
				return (0);
			else
			{
				stack[top] = 0;
				top--;
			}
		}
		i++;
	}
	if (stack[top] == 0)
		return (1);
	return (0);
}
