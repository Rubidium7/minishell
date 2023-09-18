/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:06:16 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 12:25:47 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putendl_fd("system call failed in setting up process🕷🕸", 2);
	if (type == TOKEN_ERROR)
		ft_putendl_fd("system call failed in tokenizing process🕷🕸", 2);
	if (type == PARSE_ERROR)
		ft_putendl_fd("system call failed in parsing process🕷🕸", 2);
	if (type == HEREDOC_ERROR)
		ft_putendl_fd("system call failed in heredoc process🕷🕸", 2);
	if (type == WILDCARD_ERROR)
		ft_putendl_fd("system call failed in heredoc process🕷🕸", 2);
	if (type == EXEC_ERROR)
		ft_putendl_fd("system call failed in executing process🕷🕸", 2);
	if (type == PROMPT_ERROR)
		ft_putendl_fd("problem getting the fancy prompt🕷🕸", 2);
	if (type == HISTORY_ERROR)
		ft_putendl_fd("problem fetching the history file🕷🕸", 2);
}

void	print_file_error(char *filename, t_error_code type)
{
	ft_putstr_fd(ERROR_SHROOM, 2);
	if (type != HEREDOC_FILE_ERROR)
		ft_putstr_fd(filename, 2);
	if (type == NO_RIGHTS)
		ft_putendl_fd(": Permission denied", 2);
	if (type == NO_FILE)
		ft_putendl_fd(": No such file or directory", 2);
	if (type == HEREDOC_FILE_ERROR)
		ft_putendl_fd("heredoc file open error", 2);
	if (type == AMBIGUOUS)
		ft_putendl_fd(": ambiguous redirect", 2);
}
