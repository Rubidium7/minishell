/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:58:41 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/14 13:07:19 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list_len(t_env *env_list)
{
	int	res;

	res = 0;
	while (env_list)
	{
		env_list = env_list->next;
		res++;
	}
	return (res);
}

char	*join_three_strings(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*res;

	// doesn't handle NULLs as arguments
	temp = ft_strjoin(s1, s2); // malloc
	if (!temp)
		return (NULL);
	res = ft_strjoin(temp, s3); // malloc
	free(temp);
	if (!res)
		return (NULL);
	return (res);
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
		res[i] = join_three_strings();// TODO
	}
}

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
		if (!res)
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
		if (matching_env)
		{
			core->cur_process.error_index = MALLOC_FAIL;
			return (TRUE);
		}
		core->env_list = matching_env;
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
		reeturn (TRUE);
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


/* 
t_env	*add_env_var(t_env *env_list, const char *key, const char *content)
{
	t_env	*curr_env;

	curr_env = env_list;
	while (curr_env && curr_env->next)
	{
		curr_env = curr_env->next;
	}
	if (curr_env)
	{
		curr_env->next = create_env_var(key, content);
		if (!curr_env->next)
		{
			return (NULL);
		}
		return (env_list);
	}
	else
	{
		curr_env = create_env_var(key, content);
		if (!curr_env->next)
		{
			return (NULL);
		}
		return (curr_env);
	}
} 
*/