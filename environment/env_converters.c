/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_converters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:57:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 14:30:28 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	array_to_env_list(char **ar, t_shell *core, t_bool is_setup)
{
	int		i;
	int		len;

	len = ar_len(ar);
	i = 0;
	while (i < len)
	{
		if (add_env_from_string(core, ar[i]))
			return (TRUE);
		i++;
	}
	if (is_setup)
		return (set_env("OLDPWD", NULL, core));
	return (FALSE);
}

char	**env_list_to_array(t_env *env_list, t_shell *core)
{
	char	**res;
	int		len;
	int		i;

	len = env_list_len(env_list);
	res = malloc(sizeof(t_env *) * (len + 1));
	if (!res)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (NULL);
	}
	res[len] = NULL;
	i = 0;
	while (i < len)
	{
		if (env_list->content)
			res[i] = join_three_strings(env_list->key, "=", env_list->content);
		else
			res[i] = ft_strdup(env_list->key);
		if (!res[i])
		{
			free_ar(res);
			core->cur_process.error_index = MALLOC_FAIL;
			return (NULL);
		}
		env_list = env_list->next;
		i++;
	}
	return (res);
}