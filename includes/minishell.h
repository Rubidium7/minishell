/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:28:18 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 17:06:40 by vvagapov         ###   ########.fr       */
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
# include <dirent.h>

t_bool g_sigint_received;

void	rl_replace_line(const char *text, int clear_undo);

//core
// process_line.c
void	process_line(t_shell *core, char *input);

//history.c
t_bool	fetch_history_file(t_shell *core);
void	add_to_history_file(t_shell *core);
void	add_to_history(char *str, t_shell *core);

//fancy_prompt.c
void	readline_pretty(t_shell *core);

// tokenize

//tokenize.c
void	zero_values(t_token *new);
t_token	*tokenize(char *str, t_shell *core);

// clean_token_list.c
t_token	*clean_quotes_and_whitespaces(t_token *head, t_token *current);

//redirection_filenames.c
void	mark_redirections(t_token *current);
void	save_redirection_filenames(t_token *current);

// parse
// parse.c
void		parse(t_shell *core);

// preliminary_syntax_checking.c
void	preliminary_syntax_check(t_shell *core);

// syntax_checking.c
t_ast		*syntax_check(t_token *head, t_shell *core);

// form_tree.c
t_ast		*form_tree(t_token *start, t_ast *up, int end_index, int *error_index);

// form_pipeline.c
t_pipeline	*form_pipeline(t_token *head_token, int end_index, int *error_index);

// tree_execution.c
t_command	*form_command_list(t_pipeline *current, t_shell *core, t_heredoc *heredoc);
int			execute_tree(t_ast *tree, t_shell *core);

// redirections
// redirections.c
void	open_redirections(t_command *new, t_pipeline *pipeline, t_heredoc *heredoc, t_shell *core);

// heredoc.c
t_heredoc	*open_heredocs(t_pipeline *pipeline, int index, t_shell *core);

// heredoc_signals.c
void	set_heredoc_mode(t_shell *core, int mode);

// go_through_heredocs.c
t_bool	go_through_heredocs(t_ast *tree, t_shell *core);

// ENVIRONMENT
// env_converters.c
t_bool	array_to_env_list(char **ar, t_shell *core, t_bool is_setup);
char	**env_list_to_array(t_env *env_list, t_shell *core);

// env_from_string.c
t_bool	add_env_from_string(t_shell *core, char *str);

// env_list_utils_add.c
t_env	*create_env_var(const char *key, const char *content);
t_env	*add_node_to_end(t_env *env_list, t_env *new_node);

// env_list_utils_delete.c
t_bool	delete_next(t_env *env_list);
t_env	*delete_first(t_env *env_list);
void	clear_env_list(t_env *env_list);

// env_list_utils_search.c
t_env	*find_env(t_env *env_list, const char *key);
t_env	*find_prev(t_env *env_list, const char *key);

// env_list_utils.c
int		env_list_len(t_env *env_list);

// environment_tools.c
char	*fetch_env(const char *key, t_shell *core);
t_bool	set_env(const char *key, const char *content, t_shell *core);
t_bool	unset_env(const char *key, t_shell *core);
void	print_envs(int mode, t_shell *core);

//expand_envs_in_string.c
char	*expand_envs_in_string(char *str, t_shell *core);

//expand_envs.c
t_bool	expand_envs(t_token *head, t_shell *core);

// SETUP

// set_data.c
void	set_start_data(t_shell *core, char **start_env);

// set_input_mode.c
void	set_input_mode_signals(void);
void	ignore_signals(void);
void	set_termios(t_terminal *term);
void	set_input_mode(t_shell *core, int mode);

//manage_child_signals.c
void	child_ctrl_c(int signum);
void	child_ctrl_slash(int signum);
void	set_child_signals(void);
int		process_exit_status(int ret, t_shell *core);
void	print_terminating_signal(int signum);

// signal_handlers.c
void	heredoc_ctrl_c_handler(int signum);
void	ctrl_c_handler(int signum);
void	ctrl_d_handler(t_shell *core);

//wildcards
//save_wildcards.c
t_token		*clean_non_wildcards(t_token *head, t_token *current);
void		save_wildcards(t_token *current);

//expand_wildcards.c
t_token	*find_matches(t_wildcard *wildcard);
t_token	*expand_wildcards(t_token *head);

//wildcard_matching.c
t_bool	is_wildcard_match(char *file, t_wildcard *wildcard);

//format_wildcard_into_string.c
char	*format_wildcard_into_string(t_wildcard *current);

//wildcards_in_filenames.c
void	wildcards_in_filenames(t_token *current);

//ft_ls.c
char	**ft_ls(void);

//utilities

//token_list_utils.c
// array_utils.c
void	free_ar(char **array);
char	**copy_array(char **src);
int		ar_len(char **ar);

// list_utils.c
t_token	*remove_from_token_list(t_token *head, t_token *target);
t_token	*last_token(t_token *current);
int		find_token(t_token *start, int end_index, t_token_type type);
void	free_token_node(t_token *node);

// tokenizing_utils.c
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
char	*join_three_strings(const char *s1, const char *s2, const char *s3);

//debug_utils.c
void	test_file(const char *str);
void	print_token_list(t_token *current, int print_quotes);
void	print_token(t_token *token, int new_line);
void	print_tree_in_execution_order(t_ast *tree);
void	print_file(const char *filename, int write_fd);
void	print_heredocs(t_ast *tree, int print_files);
void	print_ar(char **array);

// ast_utils.c
t_ast	*new_ast_node(t_ast *up, t_pipeline *head, \
	t_token_type type, int *error_index);
t_token	*node_at_index(t_token *current, int end_index);
int		previous_position(t_token *head, t_token *last);
t_token	*last_node(t_token *current, t_token *end);
int		token_after_parentheses(t_token *current, int end_index);	
int		find_logic_token(t_token *current, int end_index);

// exiting.c
int		handle_exit(t_shell *core);

// errors.c
void	handle_error_value(int *error_index, int position);
void	update_error_value(t_shell *core);
void	error_print(t_error_code type);
void	print_file_error(char *filename, t_error_code type);
t_bool	syntax_error(t_syntax_error type, t_token *token);

//cleaners.c
void	empty_wildcard_list(t_wildcard *current);
void	empty_token_list(t_token *current);
void	empty_heredoc_list(t_heredoc *current);
void	free_command_node(t_command *node);
void	empty_command_list(t_command *current);
void	empty_pipeline_list(t_pipeline *current);
t_ast	*free_tree(t_ast *tree);
void	clean_up(t_shell *core);

//is_token.c
t_bool	is_redir(t_token_type type);
t_bool	is_red_or_word(t_token_type type);
t_bool	is_ok_after_logic(t_token_type type);
t_bool	is_logic(t_token_type type);

// EXECUTOR
// builtins_utils.c
int		run_builtin(t_shell *core, t_command *command, t_bool is_child);
int		is_builtin(t_command *command);

// command_list_utils.c
int		list_len(t_command *list);

// command_utils.c
int		is_first_command(t_command *command);
int		is_last_command(t_command *command);
int		has_args(char **args);
t_bool	no_children_needed(t_command *commands);

// dup.c
int		dup_input(t_command *command, int **pipes);
int		dup_output(t_command *command, int **pipes);

// memory_utils.c
int		**malloc_pipes(int num);
void	free_pipes(int **pipes);

// path_utils.c
char	*find_exe_path(t_shell *core, t_command *command);

// pipeline_execution.c
int		pipeline_execution(t_shell *core, t_command *commands);

// pipes_utils.c
int		open_pipes(int **pipes);
void	close_pipes(int **pipes);

// prepare_and_finalise_pipeline.c
int		prepare_pipes_and_children(t_shell *core, int ***pipes,
	pid_t **children, int len);
int		finalise_pipes_and_children(int **pipes, pid_t *children, int len);

// BUILTINS
// pwd.c
int		pwd(t_shell *core);
// env.c
int		env(t_shell *core);
// echo.c
int		echo(t_command *command);
// export.c
int		export(t_shell *core, t_command *command);
// exit.c
long long int	ft_exit(t_shell *core, t_command *command, t_bool is_child);
// unset.c
int		unset(t_shell *core, t_command *command);
// cd.c
int		cd(t_shell *core, t_command *command);

#endif
