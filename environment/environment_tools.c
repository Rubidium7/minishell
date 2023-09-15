/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:58:41 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/15 21:01:22 by vvagapov         ###   ########.fr       */
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
		if (env_list->content)
			res[i] = join_three_strings(env_list->key, "=", env_list->content);
		else
			res[i] = ft_strdup(env_list->key);
		if (!res[i])
		{
			// ft_putstr_fd("string joining failure\n", 2);
			free_ar(res);
			core->cur_process.error_index = MALLOC_FAIL;
			return (NULL);
		}
		env_list = env_list->next;
		i++;
	}
	return (res);
}

int	ar_len(char **ar)
{
	int	res;

	res = 0;
	while (ar[res])
		res++;
	return (res);
}

int	parse_env_str(char **key, char **content, char *str)
{
	int		len;
	int		equal_index;
	
	if (!is_env_first_char(str[0]))
		return (INVALID_IDENTIFIER);
	len = ft_strlen(str);
	equal_index = 1;
	while (equal_index < len && str[equal_index] != '=')
	{
		if (!is_env_char(str[equal_index]))
			return (INVALID_IDENTIFIER);
		equal_index++;
	}
	if (equal_index == len)
		*content = NULL;
	else
	{
		*content = ft_substr(str, equal_index + 1, len - equal_index - 1);
		if (!(*content))
			return (MALLOC_FAIL);
	}
	*key = ft_substr(str, 0, equal_index);
	if (!(*key))
		return (MALLOC_FAIL);
	return (SUCCESS);
}

//
t_bool	add_env_from_string(t_shell *core, char *str)
{
	t_internal_values	ret;
	char				*key;
	char				*content;
	
	ret = parse_env_str(&key, &content, str);
	if (ret == MALLOC_FAIL)
	{
		// ft_putstr_fd("parse_env_str returned NULL\n", 2);
		core->cur_process.error_index = MALLOC_FAIL;
		return (TRUE);
	}
	else if (ret == INVALID_IDENTIFIER)
	{
		// should this be a separate error like this?
		core->cur_process.error_index = INVALID_IDENTIFIER;
		ft_putstr_fd(ERROR_SHROOM, 2);
		ft_putstr_fd(" export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (TRUE);
	}
	/* ft_putstr_fd("key: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(", content: ", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("\n", 2); */
	return(set_env(key, content, core));
}

t_bool	array_to_env_list(char **ar, t_shell *core, t_bool is_setup)
{
	int		i;
	int		len;

	len = ar_len(ar);
	i = 0;
	while (i < len)
	{
		if (add_env_from_string(core, ar[i]))
		{
			return (TRUE);
		}
		i++;
	}
	if (is_setup)
		return (set_env("OLDPWD", NULL, core));
	return (FALSE);
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
		{
			//ft_putstr_fd("strdup content returned NULL\n", 2);
			core->cur_process.error_index = MALLOC_FAIL;
		}
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
			//ft_putstr_fd("content shouldn't be NULL but it is after strdup\n", 2);
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
			//ft_putstr_fd("create_env_var returned NULL\n", 2);
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

void print_envs(int mode, t_shell *core)
{
	t_env	*curr_env;

	(void)mode; //TODO
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