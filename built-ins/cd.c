/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:10 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 21:15:10 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Updates OLDPWD with old_path and PWD with current path
static t_bool	set_pwd_envs(t_shell *core, const char *old_path)
{
	char		curr_path[PATH_MAX_LEN + 1];

	if (set_env("OLDPWD", old_path, core)
		|| !getcwd(curr_path, PATH_MAX_LEN)
		|| set_env("PWD", curr_path, core))
		return (TRUE);
	return (FALSE);
}
// Saves old path;
// navigates to the new path, throwing errors is necessary;
// updates OLDPWD and PWD env variables with old and new paths
t_bool	cd_navigate(t_shell *core, char *arg)
{
	char		old_path[PATH_MAX_LEN + 1];
	struct stat	statbuf;
	
	if (!getcwd(old_path, PATH_MAX_LEN))
		return (TRUE);
	if (chdir(arg) == -1)
	{
		if (!ft_strlen(arg))
			return (FALSE);
		stat(old_path, &statbuf);
		if(!access(arg, F_OK) && S_ISDIR(statbuf.st_mode))
			print_generic_error("cd", arg, "Not a directory");
		else
			print_generic_error("cd", arg, "No such file or directory");
		return (TRUE);
	}
	if (set_pwd_envs(core, old_path))
		return (TRUE);
	return (FALSE);
}

// runs cd on an env variable, throws errors if necessary
int	cd_env(t_shell *core, const char *env_var, const char *error_msg)
{
	char	*path;
	int		ret;
	
	path = fetch_env(env_var, core);
	if (!path)
	{
		if (core->cur_process.error_index != MALLOC_FAIL)
			print_generic_error("cd", NULL, error_msg);
		return (TRUE);
	}
	ret = cd_navigate(core, path);
	free(path);
	return (ret);
}

int	cd(t_shell *core, t_command *command)
{
	if (!command->cmd_ar[1])
		return (cd_env(core, "HOME", "🏠HOME not set"));
	else if (!ft_strcmp(command->cmd_ar[1], "-"))
		return (cd_env(core, "OLDPWD", "🔎OLDPWD not set"));
	return (cd_navigate(core, command->cmd_ar[1]));
}
