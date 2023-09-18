/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fancy_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:33:26 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 17:56:01 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	combine = ft_strjoin(B " git:" CY, branch);
	free(branch);
	if (!combine)
		return (dir);
	branch = ft_strjoin(dir, combine);
	free(combine);
	if (!branch)
		return (dir);
	free(dir);
	return (branch);
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
	tmp = ft_strjoin(" "Y, tmp);
	if (!tmp)
		return (NULL);
	current_directory = ft_strjoin(tmp, C "");
	free(tmp);
	if (!current_directory)
		return (NULL);
	return (get_git(current_directory));
}

char	*add_prompt_ret(char *tmp, int ret)
{
	char	*number;
	char	*combine;

	number = ft_itoa(ret);
	if (!number)
		return (free(tmp), NULL);
	combine = ft_strjoin(tmp, R " [");
	free(tmp);
	if (!combine)
		return (NULL);
	tmp = ft_strjoin(combine, number);
	free(combine);
	free(number);
	return (tmp);
}

char	*get_fancy_prompt(int ret)
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
	{
		tmp = add_prompt_ret(tmp, ret);
		if (!tmp)
			return (NULL);
		complete_prompt = ft_strjoin(tmp, "] ➜ "C);
	}
	else
		complete_prompt = ft_strjoin(tmp, G " ➜ "C);
	free(tmp);
	return (complete_prompt);
}
