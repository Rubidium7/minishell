/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:02:41 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 22:16:44 by vvagapov         ###   ########.fr       */
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
	int		ret;
	char	*key;
	char	*content;

	ret = parse_env_str(&key, &content, str);
	if (ret == MALLOC_FAIL)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (TRUE);
	}
	else if (ret == INVALID_IDENTIFIER)
	{
		print_generic_error("export", str, "not a valid identifier");
		return (TRUE);
	}
	ret = set_env(key, content, core);
	free(key);
	free(content);
	return (ret);
}
