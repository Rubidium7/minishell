/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:02:41 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 14:32:29 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_env_str(char **key, char **content, char *str)
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

t_bool	add_env_from_string(t_shell *core, char *str)
{
	t_internal_values	ret;
	char				*key;
	char				*content;

	ret = parse_env_str(&key, &content, str);
	if (ret == MALLOC_FAIL)
	{
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
	return (set_env(key, content, core));
}
