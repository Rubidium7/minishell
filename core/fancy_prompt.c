


#include "minishell.h"

char	*get_git(char *dir)
{
	int		fd;
	char	*tmp;
	char	*branch;
	char	*combine;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd < 0)
		return (dir);
	tmp = get_next_line(fd);
	close(fd);
	if (!tmp)
		return (dir);
	branch = ft_strrchr(tmp, '/') + 1;
	if (!branch)
		return (free(tmp), dir);
	
}

char	*get_dir_info(void)
{
	char	dir_path[256];
	char	*current_directory;
	char	*tmp;

	if (!getcwd(dir_path, sizeof(dir_path)))
		return (NULL);
	tmp = ft_strrchr(dir_path, '/') + 1;
	if (!tmp)
		return (NULL);
	tmp = ft_strjoin("[", tmp);
	if (!tmp)
		return (NULL);
	current_directory = ft_strjoin(tmp, "]");
	free(tmp);
	if (!current_directory)
		return (NULL);
	return (get_git(current_directory));
}

static char	*get_fancy_prompt(void)
{
	char	*dir_info;
	char	*tmp;
	char	*complete_prompt;

	dir_info = get_dir_info();
	if (!dir_info)
		return (NULL);
	tmp = ft_strjoin("🍄"W"Mini"C R"Shroom "C, dir_info);
	free(dir_info);
	if (!tmp)
		return (NULL);
	complete_prompt = ft_strjoin(tmp, "> ");
	free(tmp);
	return (complete_prompt);
}

void	readline_pretty(t_shell *core)
{
	char	*tmp;
	char	*fancy_prompt;

	core->cur_process.input_line = NULL;
	fancy_prompt = get_fancy_prompt();
	if (!fancy_prompt)
	{
		error_print(PROMPT_ERROR);
		tmp = readline("🍄"W"Mini"C R"Shroom"C"> ");
	}
	else
		tmp = readline(fancy_prompt);
	if (fancy_prompt)
		free(fancy_prompt);
	core->cur_process.input_line = tmp;
}