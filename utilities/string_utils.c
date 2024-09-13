/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:18:08 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 12:27:10 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_string_section(char *str, int start, int end)
{
	int		size;
	char	*ans;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	if (!str || start < 0 || end < 0 || end <= start
		|| (((int)ft_strlen(str)) - end - start) < 0)
		return (str);
	size = ft_strlen(str) - (end - start);
	ans = malloc(sizeof(char) * (size + 1));
	if (!ans)
		return (free(str), NULL);
	while (str[i])
	{
		if (!(i >= start && i < end))
		{
			ans[i2] = str[i];
			i2++;
		}
		i++;
	}
	ans[i2] = '\0';
	return (free(str), ans);
}

void	add_content(char *str, int *i, char *content)
{
	int	i2;

	i2 = 0;
	while (content[i2])
	{
		str[*i] = content[i2];
		*i += 1;
		i2++;
	}
}

char	*add_string_to(char *str, char *content, int start)
{
	int		size;
	char	*ans;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	if (!str || !ft_strlen(content) || start < 0)
		return (str);
	size = ft_strlen(str) + ft_strlen(content);
	ans = malloc(sizeof(char) * (size + 1));
	if (!ans)
		return (free(str), NULL);
	while (str[i])
	{
		if (i == start)
			add_content(ans, &i2, content);
		ans[i2] = str[i];
		i2++;
		i++;
	}
	if (i2 != size)
		add_content(ans, &i2, content);
	ans[i2] = '\0';
	return (free(str), ans);
}

char	*join_three_strings(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*res;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, s3);
	free(temp);
	if (!res)
		return (NULL);
	return (res);
}
