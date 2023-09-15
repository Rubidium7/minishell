

#include "minishell.h"

static void	fill_history(int fd)
{
	char	*buffer;

	while (SHROOM_TIME)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			return ;
		ft_strlcpy(buffer, buffer, ft_strlen(buffer));
		add_history(buffer);
		free(buffer);
	}
}

void	add_to_history_file(char *str, t_shell *core)
{
	int		fd;
	char	*path;

	path = ft_strjoin(core->tmp_dir, HISTORY_FILE);
	if (!path)
		return ;
	fd = open(path, O_APPEND | O_RDWR);
	free(path);
	if (fd < 0)
		return ;
	ft_putendl_fd(str, fd);
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
	fill_history(fd);
	close(fd);
	return (free(path), TRUE);
}

void	add_to_history(char *str, t_shell *core)
{
	if (ft_strncmp(str, "", 1))
	{
		add_history(str);
		if (core->history_saving)
			add_to_history_file(str, core);
	}
}