/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shell_level.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:07:35 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 22:12:00 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	increment_shell_level(t_shell *core)
{
	char	*level;
	int		num;
	t_bool	ret;

	level = fetch_env("SHLVL", core);
	if (!level)
		return (set_env("SHLVL", "1", core));
	num = ft_atoi(level);
	free(level);
	num++;
	if (num < 0)
		num = 0;
	level = ft_itoa(num);
	if (!level)
		return (TRUE);
	ret = set_env("SHLVL", level, core);
	free(level);
	return (ret);
}
