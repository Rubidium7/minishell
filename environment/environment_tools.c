/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:58:41 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 16:26:57 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fetches env variable content by key.
// RETURNS: string with copy of content on success, NULL on failure
char	*fetch_env(const char *key, t_shell *core)
{
	t_env	*matching_env;
	char	*res;

	if (!key)
		return (NULL);
	matching_env = find_env(core->env_list, key);
	if (matching_env)
	{
		res = ft_strdup(matching_env->content);
		if (matching_env->content && !res)
			core->cur_process.error_index = MALLOC_FAIL;
		return (res);
	}
	return (NULL);
}

// If variable with given key already exists, updates the content.
// Otherwise creates a new variable with given key and content.
// RETURNS: FALSE on success, TRUE on failure 
t_bool	set_env(const char *key, const char *content, t_shell *core)
{
	t_env	*matching_env;

	matching_env = find_env(core->env_list, key);
	if (matching_env)
	{
		free(matching_env->content);
		matching_env->content = ft_strdup(content);
		if (!matching_env->content && content)
		{
			core->cur_process.error_index = MALLOC_FAIL;
			return (TRUE);
		}
		return (FALSE);
	}
	else
	{
		matching_env = create_env_var(key, content);
		if (!matching_env)
		{
			core->cur_process.error_index = MALLOC_FAIL;
			return (TRUE);
		}
		core->env_list = add_node_to_end(core->env_list, matching_env);
		return (FALSE);
	}
}

// If variable with given key exists, deletes it.
// RETURNS:
// - FALSE on successful removal
// - TRUE if variable not found
t_bool	unset_env(const char *key, t_shell *core)
{
	t_env	*matching_env_prev;

	if (!core->env_list)
		return (TRUE);
	matching_env_prev = find_prev(core->env_list, key);
	if (matching_env_prev && !matching_env_prev->next)
		return (TRUE);
	else
	{
		if (matching_env_prev)
		{
			delete_next(matching_env_prev);
		}
		else
		{
			core->env_list = delete_first(core->env_list);
		}
		return (FALSE);
	}
}

void	print_envs(int mode, t_shell *core)
{
	t_env	*curr_env;

	curr_env = core->env_list;
	while (curr_env)
	{
		if (!((mode == EXPORT && !ft_strcmp("_", curr_env->key))
				|| (mode == ENV && !curr_env->content)))
		{
			if (mode == EXPORT)
				ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(curr_env->key, 1);
			if (curr_env->content)
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd(curr_env->content, 1);
			}
			if (mode == EXPORT || curr_env->content)
				ft_putstr_fd("\n", 1);
		}
		curr_env = curr_env->next;
	}
}
