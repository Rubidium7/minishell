/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:34:48 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 16:43:28 by vvagapov         ###   ########.fr       */
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

char	*heredoc_prompt(t_shell *core)
{
	char	*buffer;

	set_heredoc_mode(core, ON);
	buffer = readline("🐊"CY"here"C G"croc> "C);
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

static t_heredoc	*replace_old(t_heredoc *new)
{
	if (new)
	{
		free(new->filename);
		free(new);
	}
	new = malloc(sizeof(t_heredoc));
	return (new);
}

t_heredoc	*heredoc(t_token *current, t_heredoc *new, int index, t_shell *core)
{
	int	fd;

	core->cur_process.error_index = MALLOC_FAIL;
	new = replace_old(new);
	if (!new)
		return (NULL);
	new->filename = \
	create_heredoc_file(core->cur_process.heredoc_index, core);
	if (!new->filename)
		return (free(new), NULL);
	core->cur_process.heredoc_index++;
	new->index = index;
	new->next = NULL;
	fd = open(new->filename, O_CREAT | O_WRONLY, 0000644);
	if (fd < 0)
	{
		core->cur_process.error_index = OPEN_ERROR;
		return (free(new->filename), free(new), NULL);
	}
	core->cur_process.error_index = SUCCESS;
	return (heredoc_input(fd, current->filename, !current->quote, core), new);
}

t_heredoc	*open_heredocs(t_pipeline *pipeline, int index, t_shell *core)
{
	t_heredoc	*new;
	t_token		*current;

	current = pipeline->start;
	new = NULL;
	while (current != pipeline->end)
	{
		if (current->type == HEREDOC)
		{
			new = heredoc(current, new, index, core);
			if (core->cur_process.error_index != SUCCESS)
				return (free(new->filename), free(new), NULL);
		}
		current = current->next;
	}
	return (new);
}
