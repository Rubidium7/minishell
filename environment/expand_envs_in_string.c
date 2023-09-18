/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs_in_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:58:52 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/13 13:58:54 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_return_value(char *str, int start, t_shell *core)
{
	char	*number;
	
	str = remove_string_section(str, start - 1, start + 1);
	if (!str)
		return (NULL);
	number = ft_itoa(core->cur_process.ret);
	if (!number)
		return (free(str), NULL);
	str = add_string_to(str, number, start - 1);
	free(number);
	return (expand_envs_in_string(str, core));
}

char	*get_key(char *str, int start, int end)
{
	int		size;
	char	*key;
	int		i;

	i = 0;
	size = end - start;
	key = malloc(sizeof(char) * (size + 1));
	if (!key)
		return (NULL);
	while (start != end)
	{
		key[i] = str[start];
		i++;
		start++;
	}
	key[i] = '\0';
	return (key);
}

char	*expand_env(char *str, int start, int end, t_shell *core)
{
	char	*key;
	char	*content;

	key = get_key(str, start, end);
	if (!key)
		return (free(str), NULL);
	content = fetch_env(key, core);
	free(key);
	if (core->cur_process.error_index == MALLOC_FAIL)
		return (free(str), NULL);
	str = remove_string_section(str, start - 1, end);
	if (!str)
	{
		if (content)
			free(content);
		return (NULL);
	}
	if (!content)
		return (expand_envs_in_string(str, core));
	str = add_string_to(str, content, start - 1);
	free(content);
	if (!str)
		return (NULL);
	return (expand_envs_in_string(str, core));
}

char	*expand_envs_in_string(char *str, t_shell *core)
{
	int		i;
	int		start;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				return (expand_return_value(str, i, core));
			start = i;
			while (str[i] && is_env_char(str[i]))
				i++;
			if (i != start)
				return (expand_env(str, start, i, core));
		}
		i++;
	}
	return (str);
}