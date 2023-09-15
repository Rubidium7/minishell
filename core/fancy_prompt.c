


#include "minishell.h"

char	*get_branch_name(void)
{
	int		fd;
	char	*tmp;
	char	*branch;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd < 0)
		return (NULL);
	tmp = get_next_line(fd);
	close(fd);
	ft_strlcpy(tmp, tmp, ft_strlen(tmp));
	branch = ft_strrchr(tmp, '/') + 1;
	if (!branch)
		return (free(tmp), NULL);
	branch = ft_strdup(branch);
	free(tmp);
	return (branch);
}

char	*get_git(char *dir)
{
	char	*branch;
	char	*combine;

	branch = get_branch_name();
	if (!branch)
		return (dir);
	combine = ft_strjoin("["M "git:" CY "(" B, branch);
	free(branch);
	if (!combine)
		return (dir);
	branch = ft_strjoin(combine, CY ")"C "]");
	free(combine);
	if (!branch)
		return (dir);
	combine = ft_strjoin(dir, branch);
	free(branch);
	if (!combine)
		return (dir);
	free(dir);
	return (combine);
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
	tmp = ft_strjoin("["Y, tmp);
	if (!tmp)
		return (NULL);
	current_directory = ft_strjoin(tmp, C "]");
	free(tmp);
	if (!current_directory)
		return (NULL);
	return (get_git(current_directory));
}

static char	*get_fancy_prompt(t_bool ret)
{
	char	*dir_info;
	char	*tmp;
	char	*complete_prompt;

	dir_info = get_dir_info();
	if (!dir_info)
		return (NULL);
	tmp = ft_strjoin(MINI_SHROOM, dir_info);
	free(dir_info);
	if (!tmp)
		return (NULL);
	if (ret)
		complete_prompt = ft_strjoin(tmp, R "> "C);
	else
		complete_prompt = ft_strjoin(tmp, G "> "C);
	free(tmp);
	return (complete_prompt);
}

void	readline_pretty(t_shell *core)
{
	char	*tmp;
	char	*fancy_prompt;

	core->cur_process.input_line = NULL;
	fancy_prompt = get_fancy_prompt(!(!core->cur_process.ret));
	if (!fancy_prompt)
	{
		error_print(PROMPT_ERROR);
		if (core->cur_process.ret)
			tmp = readline(MINI_SHROOM R "> "C);
		else
			tmp = readline(MINI_SHROOM G "> "C);
	}
	else
		tmp = readline(fancy_prompt);
	if (fancy_prompt)
		free(fancy_prompt);
	core->cur_process.input_line = tmp;
}