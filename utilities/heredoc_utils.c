/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:58:12 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 17:58:15 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_file(int heredoc_index, t_shell *core)
{
	char	*number;
	char	*path;
	char	*filename;

	number = ft_itoa(heredoc_index);
	if (!number)
		return (NULL);
	filename = ft_strjoin(".heredoc_tmp", number);
	free(number);
	if (!filename)
		return (NULL);
	path = ft_strjoin(core->tmp_dir, filename);
	if (!path)
		return (filename);
	free(filename);
	return (path);
}

static char	*heredoc_prompt(t_shell *core)
{
	char	*buffer;

	set_heredoc_mode(core, ON);
	buffer = readline(CY"here"C G"doc> "C);
	set_heredoc_mode(core, OFF);
	return (buffer);
}

t_bool	heredoc_input(int fd, char *limiter, t_bool expand, t_shell *core)
{
	pid_t	child;
	char	*buffer;

	child = fork();
	while (!child)
	{
		buffer = heredoc_prompt(core);
		if (!buffer || !ft_strncmp(buffer, limiter, ft_strlen(buffer) + 1))
		{
			if (buffer)
				free(buffer);
			exit(0);
		}
		if (expand)
			buffer = expand_envs_in_string(buffer, core);
		if (!buffer)
			return (error_print(HEREDOC_ERROR), exit(2), TRUE);
		ft_putendl_fd(buffer, fd);
		free(buffer);
	}
	waitpid(child, &core->cur_process.error_index, 0);
	close(fd);
	core->cur_process.error_index = WEXITSTATUS(core->cur_process.error_index);
	return (!(!core->cur_process.error_index));
}
