/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_wildcard_into_string.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:13:30 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/14 15:13:34 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_wildcard_string(t_wildcard *current)
{
	int			size;
	char		*str;

	size = 0;
	while (current)
	{
		size += ft_strlen(current->str);
		current = current->next;
	}
	str = malloc(sizeof(char) * (size + 1));
	return (str);
}

char	*format_wildcard_into_string(t_wildcard *current)
{
	int			i;
	int			i2;
	char		*str;

	str = alloc_wildcard_string(current);
	if (!str)
		return (NULL);
	i = 0;
	while (current)
	{
		i2 = 0;
		while (current->str[i2])
		{
			if (current->expand && current->str[i2] == '*')
				str[i] = 1;
			else
				str[i] = current->str[i2];
			i++;
			i2++;
		}
		current = current->next;
	}
	str[i] = '\0';
	return (str);
}
