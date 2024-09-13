/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:35:23 by nlonka            #+#    #+#             */
/*   Updated: 2024/03/06 15:36:37 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	non_numeric_error(t_shell *core, const char *arg)
{
	print_generic_error("exit", arg, "numeric argument required");
	core->cur_process.shroom_time = FALSE;
	return (255);
}

static t_bool	is_numeric(char *str)
{
	int		i;
	t_bool	has_digits;

	i = 0;
	if (str[i] == '-')
		i++;
	has_digits = FALSE;
	while (ft_isdigit(str[i]))
	{
		has_digits = TRUE;
		i++;
	}
	if (str[i] == '\0' && has_digits)
		return (TRUE);
	return (FALSE);
}

static long long int	exit_with_arg(t_shell *core, char *arg, t_bool *success)
{
	long long int	res;
	int				overflow;
	char			*trimmed_str;

	overflow = 0;
	trimmed_str = ft_strtrim(arg, " 	​         ⠀");
	if (!trimmed_str)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		core->cur_process.shroom_time = FALSE;
		return (MALLOC_FAIL);
	}
	if (!is_numeric(trimmed_str))
	{
		free(trimmed_str);
		return (non_numeric_error(core, arg));
	}
	res = slightly_special_atoi(trimmed_str, &overflow);
	free(trimmed_str);
	if (overflow)
		return (non_numeric_error(core, arg));
	*success = TRUE;
	return (res);
}

long long int	ft_exit(t_shell *core, t_command *command, t_bool is_child)
{
	long long int	res;
	t_bool			success;

	if (!is_child)
		write(2, "exit\n", 9);
	if (!command->cmd_ar[1])
	{
		core->cur_process.shroom_time = FALSE;
		return (core->cur_process.old_ret);
	}
	success = FALSE;
	res = exit_with_arg(core, command->cmd_ar[1], &success);
	if (!success)
		return (res);
	if (command->cmd_ar[2])
	{
		print_generic_error("exit", NULL, "too many arguments");
		return (1);
	}
	core->cur_process.shroom_time = FALSE;
	return (res);
}
