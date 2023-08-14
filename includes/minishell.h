/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:28:18 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 18:36:21 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "defines.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>

void	rl_replace_line(const char *text, int clear_undo);

//core

//parsing

//parse.c

//setup

//set_data.c
void	set_start_data(t_shell *core, char **start_env);

//set_input_mode.c
void	set_input_mode_signals(t_sig *signals);
void	set_input_mode(t_shell *core, int mode);

//signal_handlers.c
void	ctrl_c_handler(int signum);
void	ctrl_d_handler(t_shell *core);

//utilities

//array_utils.c
void	free_ar(char **array);
char	**copy_array(char **src);

//exiting.c
int		handle_exit(t_shell *core);

#endif
