

#include "minishell.h"

char	*create_heredoc_file(int heredoc_index, t_shell *core)
{
	char	*number;
	char	*path;
	char	*filename;
	char	*directory;

	number = ft_itoa(heredoc_index);
	if (!number)
		return (NULL);
	filename = ft_strjoin(".heredoc_tmp", number);
	free(number);
	if (!filename)
		return (NULL);
	directory = fetch_env("TMPDIR", core);
	if (!directory)
		return (filename);
	path = ft_strjoin(directory, filename);
	free(directory);
	if (!path)
		return (filename);
	free(filename);
	return (path);
}

t_bool	heredoc_input(int fd, char *limiter, t_bool expand, t_shell *core)
{
	pid_t	child;
	char	*buffer;

	child = fork();
	while (!child)
	{
		set_heredoc_mode(core, ON);
		buffer = readline("🐊"CY"here"C G"croc> "C);
		set_heredoc_mode(core, OFF);
		if (!ft_strncmp(buffer, limiter, ft_strlen(buffer) + 1))
		{
			free(buffer);
			exit(0);
		}
		(void)expand;
		// if (expand)
		// 	buffer = expand_envs_in_string(buffer, core);
		ft_putendl_fd(buffer, fd);
		free(buffer);
	}
	waitpid(child, &core->cur_process.ret, 0);
	close(fd);
	core->cur_process.ret = WEXITSTATUS(core->cur_process.ret);
	return (!(!core->cur_process.ret));
}

t_heredoc	*heredoc(t_token *current, t_heredoc *new, int index, t_shell *core)
{
	int	fd;

	core->cur_process.ret = MALLOC_FAIL;
	if (new)
	{
		free(new->filename);
		free(new);
	}
	new = malloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->filename = \
	create_heredoc_file(core->cur_process.heredoc_index, core);
	if (!new->filename)
		return (free(new), NULL);
	core->cur_process.heredoc_index++;
	new->index = index;
	fd = open(new->filename, O_CREAT | O_WRONLY, 0000644);
	if (fd < 0)
	{
		core->cur_process.ret = OPEN_ERROR;
		return (free(new->filename), free(new), NULL);
	}
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
			if (core->cur_process.ret == MALLOC_FAIL)
				core->cur_process.error_index = MALLOC_FAIL;
			if (core->cur_process.ret)
				return (free(new->filename), free(new), NULL);
		}
		current = current->next;
	}
	return (new);
}