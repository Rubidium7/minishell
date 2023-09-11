/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:28:18 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/21 11:30:05 by nlonka           ###   ########.fr       */
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

//tokenize

//tokenize.c
t_token	*tokenize(char *str, t_shell *core);

//clean_token_list.c
t_token	*clean_quotes_and_whitespaces(t_token *head, t_token *current);

//redirection_filenames.c
void	mark_redirections(t_token *current);
void	save_redirection_filenames(t_token *current);

//parse
//parse.c
void		parse(t_shell *core);

//preliminary_syntax_checking.c
t_bool		preliminary_syntax_check(t_shell *core);

//syntax_checking.c
t_ast		*syntax_check(t_token *head, t_shell *core);

//form_tree.c
t_ast		*form_tree(t_token *start, t_ast *up, int end_index, int *error_index);

//form_pipeline.c
t_pipeline	*form_pipeline(t_token *head_token, int end_index, int *error_index);

//tree_execution.c
t_command	*form_command_list(t_pipeline *current, t_shell *core, t_heredoc *heredoc);
t_bool		execute_tree(t_ast *tree, t_shell *core);

//redirections
//redirections.c
void	open_redirections(t_command *new, t_pipeline *pipeline, t_heredoc *heredoc, t_shell *core);

//heredoc.c
t_heredoc	*open_heredocs(t_pipeline *pipeline, int index, t_shell *core);

//heredoc_signals.c
void	set_heredoc_mode(t_shell *core, int mode);

//go_through_heredocs.c
t_bool	go_through_heredocs(t_ast *tree, t_shell *core);

//environment
//environment_tools.c
char	*fetch_env(const char *key, t_shell *core);

//expand_envs_in_string.c
char	*expand_envs_in_string(char *str, t_shell *core);

//expand_envs.c
t_bool	expand_envs(t_token *head, t_shell *core);

//setup

//set_data.c
void	set_start_data(t_shell *core, char **start_env);

//set_input_mode.c
void	set_input_mode_signals(t_sig *signals);
void	ignore_signals(t_sig *signals);
void	set_termios(t_terminal *term);
void	set_input_mode(t_shell *core, int mode);

//signal_handlers.c
void	heredoc_ctrl_c_handler(int signum);
void	ctrl_c_handler(int signum);
void	ctrl_d_handler(t_shell *core);

//utilities
//array_utils.c
void	free_ar(char **array);
char	**copy_array(char **src);

//list_utils.c
t_token	*remove_from_token_list(t_token *head, t_token *target);
int		find_token(t_token *start, int end_index, t_token_type type);

//tokenizing_utils.c
char	*get_quoted_word(char *str, size_t *i, int quote, t_token *new);
char	*get_word_token(char *str, size_t *i);
void	carve_out_whitespace(char *str, size_t *i);
size_t	size_of_token(t_token_type type);
void	indexify_token_list(t_token *current); //might be useless

//character_utils.c
t_bool	is_env_first_char(char c);
t_bool	is_env_char(char c);
t_bool	is_whitespace(char c);
t_bool	is_special_char(char c);
t_bool	is_redir(t_token_type type);

//string_utils.c
char	*remove_string_section(char *str, int start, int end);
char	*add_string_to(char *str, char *content, int start);


//debug_utils.c
void	print_token_list(t_token *current, int print_quotes);
void	print_token(t_token *token, int new_line);
void	print_tree_in_execution_order(t_ast *tree);
void	print_file(const char *filename, int write_fd);
void	print_heredocs(t_ast *tree, int print_files);
void	print_ar(char **array);

//ast_utils.c
t_ast	*new_ast_node(t_ast *up, t_pipeline *head, \
	t_token_type type, int *error_index);
t_token	*node_at_index(t_token *current, int end_index);
int		previous_position(t_token *head, t_token *last);
t_token	*last_node(t_token *current, t_token *end);
int		token_after_parentheses(t_token *current, int end_index);	
int		find_logic_token(t_token *current, int end_index);

//exiting.c
int		handle_exit(t_shell *core);

//errors.c
void	handle_error_value(int *error_index, int position);
void	update_error_value(t_shell *core);
void	error_print(t_error_code type);
void	print_file_error(char *filename, t_error_code type);
t_bool	syntax_error(t_syntax_error type, t_token *token);

//cleaners.c
void	empty_token_list(t_token *current);
void	empty_heredoc_list(t_heredoc *current);
void	free_command_node(t_command *node);
void	empty_command_list(t_command *current);
void	empty_pipeline_list(t_pipeline *current);
t_ast	*free_tree(t_ast *tree);
void	clean_up(t_shell *core);

#endif
