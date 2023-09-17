/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:10 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/17 18:26:50 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: handle cd -
t_bool	set_oldpwd(t_shell *core, char *arg)
{
	char		*ret;
	char		path[PATH_MAX_LEN + 1];
	struct stat	statbuf;
	//int			access_res;
	
	//printf("set_oldpwd, arg: %s\n", arg);
	// get old path
	ret = getcwd(path, PATH_MAX_LEN);
	if (!ret)
	{
		core->cur_process.error_index = GETCWD_FAIL;
		return (TRUE);
	}
	//access_res = access(arg, F_OK);
	
	// navigate to new path and catch errors
	if (chdir(arg) == -1)
	{
		// null arg does nothing
		if (!ft_strlen(arg))
			return (FALSE);
		// check if it's a directory
		stat(path, &statbuf);
		if(!access(arg, F_OK) && S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd(ERROR_SHROOM, 1);
			ft_putstr_fd(": cd: ", 1);
			ft_putstr_fd(arg, 1);
			ft_putstr_fd(": Not a directory\n", 1);
			return (TRUE);
		}
		// otherwise not found error
		ft_putstr_fd(ERROR_SHROOM, 1);
		ft_putstr_fd(": cd: ", 1);
		ft_putstr_fd(arg, 1);
		ft_putendl_fd(": No such file or directory", 2);
		return (TRUE);
	}
	// set oldpwd
	if (set_env("OLDPWD", path, core) == TRUE)
		return (TRUE);
	// set current pwd
	ret = getcwd(path, PATH_MAX_LEN);
	if (!ret)
	{
		core->cur_process.error_index = GETCWD_FAIL;
		return (TRUE);
	}
	if (set_env("PWD", path, core) == TRUE)
		return (TRUE);
	return (FALSE);
}

int	cd(t_shell *core, t_command *command)
{
	char	*path;
	int		ret;
	
	if (!command->cmd_ar[1])
	{
		path = fetch_env("HOME", core);
		if (!path)
		{
			if (core->cur_process.error_index == MALLOC_FAIL)
			{
				return (MALLOC_FAIL);
			}
			else
			{
				// Put to 2?
				ft_putstr_fd(ERROR_SHROOM, 1);
				ft_putstr_fd(": cd: 🏠HOME not set\n", 1);
				// TODO: get rid of this
				return (HOME_NOT_SET);
			}
		}
		if (chdir(path) == -1)
		{
			free(path);
			return (TRUE);
		}
		free(path);
		return (FALSE);
	}
	else if (!ft_strcmp(command->cmd_ar[1], "-"))
	{
		path = fetch_env("OLDPWD", core);
		//printf("path: %s\n", path);
		if (!path)
		{
			//printf("path is NULL, err index: %i\n", core->cur_process.error_index);
			if (core->cur_process.error_index != MALLOC_FAIL)
			{
				ft_putstr_fd(ERROR_SHROOM, 1);
				ft_putstr_fd(": cd: 🔎OLDPWD not set\n", 1);
			}
			return (TRUE);
		}
		ret = set_oldpwd(core, path);
		free(path);
		return (ret);
	}
	return (set_oldpwd(core, command->cmd_ar[1]));
}
