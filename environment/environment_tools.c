/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:58:41 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/13 13:58:44 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fetch_env(const char *key, t_shell *core)
{
	int		i;
	char	*content;

	//should be changed, made it lazily to use for heredoc tmp file directory

	if (!core->env || !key)
		return (NULL);
	i = 0;
	while (core->env[i])
	{
		if (!ft_strncmp(key, core->env[i], ft_strlen(key))) //fucks up if similar keys like VAR & VAR1
		{
			if (core->env[i] + ft_strlen(key))
				content = ft_strdup(core->env[i] + ft_strlen(key) + 1);
			else
				content = ft_strdup(core->env[i] + ft_strlen(key));
			if (!content)
				core->cur_process.error_index = MALLOC_FAIL;
			return (content);
		}
		i++;
	}
	return (NULL);
}