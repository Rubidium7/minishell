/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:06:16 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/19 08:31:14 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_generic_error(const char *cmd, const char *arg, const char *msg)
{
	ft_putstr_fd(ERROR_SHROOM, STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
		{
			ft_putstr_fd("`", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd("': ", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	handle_error_value(int *error_index, int position)
{
	if (*error_index == DEFAULT || *error_index == UNEXPECTED_NL)
		*error_index = position;
	else if (position != UNEXPECTED_NL && position < *error_index)
		*error_index = position;
	if (*error_index != UNEXPECTED_NL && *error_index < 0)
		*error_index = UNEXPECTED_NL;
}

void	update_error_value(t_shell *core)
{
	int	error;

	error = core->cur_process.error_index;
	if (error == MALLOC_FAIL)
		core->cur_process.ret = MALLOC_ERROR;
	else
		core->cur_process.ret = error;
}

void	error_print(t_error_code type)
{
	if (type == SETUP_ERROR)
		ft_putendl_fd("system call failed in setting up process",
			STDERR_FILENO);
	if (type == TOKEN_ERROR)
		ft_putendl_fd("system call failed in tokenizing process",
			STDERR_FILENO);
	if (type == PARSE_ERROR)
		ft_putendl_fd("system call failed in parsing process", STDERR_FILENO);
	if (type == HEREDOC_ERROR)
		ft_putendl_fd("system call failed in heredoc process", STDERR_FILENO);
	if (type == WILDCARD_ERROR)
		ft_putendl_fd("system call failed in heredoc process", STDERR_FILENO);
	if (type == EXEC_ERROR)
		ft_putendl_fd("system call failed in executing process",
			STDERR_FILENO);
	if (type == HISTORY_ERROR)
	{
		ft_putendl_fd("problem fetching the history file", STDERR_FILENO);
		ft_putendl_fd("might mean that there's no TMPDIR env set", STDERR_FILENO);
	}
}

void	print_file_error(char *filename, t_error_code type)
{
	ft_putstr_fd(ERROR_SHROOM, STDERR_FILENO);
	if (type != HEREDOC_FILE_ERROR)
		ft_putstr_fd(filename, STDERR_FILENO);
	if (type == NO_RIGHTS)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	if (type == NO_FILE)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	if (type == HEREDOC_FILE_ERROR)
		ft_putendl_fd("heredoc file open error", STDERR_FILENO);
	if (type == AMBIGUOUS)
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
}
