

#include "minishell.h"

void	purge_old_file(t_command *new, t_token_type type)
{
	if (type == RED_IN || type == HEREDOC)
		close(new->red_in);
	if (type == RED_OUT || type == RED_OUT_APP)
		close(new->red_out);
	if (type == HEREDOC)
		free(new->heredoc_file);
}

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
	if (!child)
	{
		while (SHROOM_TIME)
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
	}
	waitpid(child, &core->cur_process.ret, 0);
	close(fd);
	core->cur_process.ret = WEXITSTATUS(core->cur_process.ret);
	return (!(!core->cur_process.ret));
}

t_bool	heredoc(t_command *new, t_token *current, t_shell *core)
{
	if (new->red_in != DEFAULT)
		purge_old_file(new, HEREDOC);
	new->heredoc_file = \
	create_heredoc_file(core->cur_process.heredoc_index, core);
	if (!new->heredoc_file)
	{
		core->cur_process.ret = MALLOC_FAIL;
		return (TRUE);
	}
	core->cur_process.heredoc_index++;
	new->red_in = open(new->heredoc_file, O_CREAT | O_WRONLY, 0000644);
	if (new->red_in < 0)
	{
		core->cur_process.ret = OPEN_ERROR;
		return (TRUE);
	}
	if (heredoc_input(new->red_in, current->filename, !current->quote, core))
		return (TRUE);
	new->red_in = open(new->heredoc_file, O_RDONLY);
	return (FALSE);
}

t_command	*open_heredocs(t_command *new, t_pipeline *pipeline, t_shell *core)
{
	t_token	*current;

	current = pipeline->start;
	while (current != pipeline->end)
	{
		if (current->type == HEREDOC)
		{
			if (heredoc(new, current, core))
				return (free_command_node(new), NULL);
			print_file(new->red_in, 1); //debug
		}
		current = current->next;
	}
	return (new);
}