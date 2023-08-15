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
//process_line.c
void	process_line(t_shell *core, char *input);

//parsing
//parse.c

//tokenize.c
t_token	*tokenize(char *input);

//clean_token_list.c
t_token	*clean_quotes_and_whitespaces(t_token *head);

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

//tokenizing_utils.c
char	*get_quoted_word(char *str, size_t *i, int quote, t_token *new);
char	*get_word_token(char *str, size_t *i);
void	carve_out_whitespace(char *str, size_t *i);
size_t	size_of_token(t_token_type type);

//character_utils.c
int 	is_whitespace(char c);
int 	is_special_char(char c);

//debug_utils.c
void	print_token_list(t_token *current);
void	print_ar(char **array);

//exiting.c
int		handle_exit(t_shell *core);

//errors.c
void	error_print(t_error_code type);

//cleaners.c
void	empty_token_list(t_token *current);

#endif
