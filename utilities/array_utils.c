/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:47:33 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 18:51:19 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ar(char **array)
{
	int	y;

	y = 0;
	if (!array)
		return ;
	while (array[y])
	{
		free(array[y]);
		y++;
	}
	free(array);
}
	

char	**copy_array(char **src)
{
	int		y;
	char	**dst;

	y = 0;
	while (src[y])
		y++;
	dst = (char **)malloc(sizeof(char *) * (y + 1));
	if (!dst)
		return (NULL);
	y = 0;
	while (src[y])
	{
		dst[y] = ft_strdup(src[y]);
		if (!dst[y])
			return (free_ar(dst), NULL);
		y++;
	}
	dst[y] = NULL;
	return (dst);
}
