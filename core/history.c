

#include "minishell.h"

static void	fill_history(int fd, t_shell *core)
{
	int		i;
	char	*buffer;

	i = 0;
	while (i != HISTORY_MAX)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			return ;
		ft_strlcpy(buffer, buffer, ft_strlen(buffer));
		add_history(buffer);
		core->history[i] = ft_strdup(buffer);
		if (!core->history[i])
			return (free(buffer));
		free(buffer);
		i++;
	}
}

void	add_to_history_file(t_shell *core)
{
	int		fd;
	char	*path;
	int		i;

	path = ft_strjoin(core->tmp_dir, HISTORY_FILE);
	if (!path)
		return ;
	fd = open(path, O_TRUNC | O_RDWR);
	free(path);
	if (fd < 0)
		return ;
	i = 0;
	while (i != HISTORY_MAX)
	{
		if (core->history[core->history_index])
			ft_putendl_fd(core->history[core->history_index], fd);
		if (core->history_index == HISTORY_MAX - 1)
			core->history_index = 0;
		else
			core->history_index++;
		i++;
	}
	close(fd);
}

t_bool	fetch_history_file(t_shell *core)
{
	int		fd;
	char	*path;

	if (!core->tmp_dir)
		return (FALSE);
	path = ft_strjoin(core->tmp_dir, HISTORY_FILE);
	if (!path)
		return (FALSE);
	fd = open(path, O_APPEND | O_RDONLY);
	if (fd < 0)
	{
		fd = open(path, O_CREAT, 0000644);
		close(fd);
		return (free(path), TRUE);
	}
	fill_history(fd, core);
	close(fd);
	return (free(path), TRUE);
}

void	add_to_history_array(char *str, t_shell *core)
{
	if (core->history[core->history_index])
		free(core->history[core->history_index]);
	core->history[core->history_index] = ft_strdup(str);
	if (core->history_index == HISTORY_MAX - 1)
		core->history_index = 0;
	else
		core->history_index++;
}

void	add_to_history(char *str, t_shell *core)
{
	if (ft_strncmp(str, "", 1))
	{
		add_history(str);
		if (core->history_saving)
			add_to_history_array(str, core);
	}
}
