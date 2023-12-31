# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/03 20:58:45 by vvagapov          #+#    #+#              #
#    Updated: 2023/09/18 23:26:30 by vvagapov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Target Binary Program
NAME = minishell

#Color scheme
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Flags
FLAGS = -Wall -Werror -Wextra -I includes -g
READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

#Directory locations
CORE_DIR = core/
TOKENIZE_DIR = tokenize/
PARSE_DIR = parse/
SETUP_DIR = setup/
RE_DIR = redirections/
ENV_DIR = environment/
WILD_DIR = wildcards/
UTILS_DIR = utilities/
OBJS_DIR = obj/
EXE_DIR = execute/
BUILTINS_DIR = built-ins/

#Sources by folder
_CORE := main.c process_line.c history.c fancy_prompt.c
_TOKENIZE := clean_token_list.c tokenize.c redirections_filenames.c
_PARSE := parse.c preliminary_syntax_checks.c \
		form_tree.c syntax_checking.c \
		tree_execution.c form_pipeline.c form_command.c
_SETUP := set_data.c set_input_mode.c manage_child_signals.c signal_handlers.c
_REDIR := redirections.c heredoc.c heredoc_signals.c go_through_heredocs.c
_ENV := environment_tools.c expand_envs_in_string.c expand_envs.c \
		env_list_utils.c env_list_utils_add.c env_list_utils_delete.c \
		env_list_utils_search.c env_converters.c env_from_string.c \
		increment_shell_level.c
_WILD := save_wildcards.c expand_wildcards.c wildcard_matching.c \
		format_wildcard_into_string.c wildcards_in_filenames.c ft_ls.c
_UTILS := array_utils.c token_list_utils.c character_utils.c string_utils.c \
		tokenizing_utils.c ast_utils.c list_cleaners.c exiting.c errors.c \
		cleaners.c is_token.c syntax_error_printing.c heredoc_utils.c \
		find_token_nodes.c
_EXE := pipeline_execution.c pipes_utils.c memory_utils.c command_list_utils.c \
		command_utils.c dup.c builtins_utils.c prepare_and_finalise_pipeline.c \
		path_utils.c
_BUILTINS := cd.c echo.c env.c exit.c exit_atoi.c export.c pwd.c unset.c

ALL_SRCS := $(addprefix $(CORE_DIR), $(_CORE)) \
			$(addprefix $(TOKENIZE_DIR), $(_TOKENIZE)) \
			$(addprefix $(PARSE_DIR), $(_PARSE)) \
			$(addprefix $(SETUP_DIR), $(_SETUP)) \
			$(addprefix $(RE_DIR), $(_REDIR)) \
			$(addprefix $(WILD_DIR), $(_WILD)) \
			$(addprefix $(ENV_DIR), $(_ENV)) \
			$(addprefix $(UTILS_DIR), $(_UTILS)) \
			$(addprefix $(EXE_DIR), $(_EXE)) \
			$(addprefix $(BUILTINS_DIR), $(_BUILTINS))

SRCS = $(_CORE) $(_TOKENIZE) $(_PARSE) $(_SETUP) $(_REDIR) $(_WILD) $(_ENV) $(_UTILS) $(_EXE) $(_BUILTINS)
OBJ_FILES = $(SRCS:.c=.o)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(SRCS:.c=.o))
INCLUDES = includes/defines.h includes/minishell.h includes/structs.h 

LIB = libft/libft.a

all: $(NAME)

$(LIB):
	@make all -C libft
	@make bonus -C libft
	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

$(NAME): $(LIB) $(OBJS_DIR) $(OBJS) $(INCLUDES)
	@cc $(FLAGS) $(OBJS) -o $@ $(READLINE) -L ./libft -lft
	@echo "$(COLOUR_GREEN)$@ created$(COLOUR_END)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(COLOUR_BLUE)object directory created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(CORE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(TOKENIZE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(PARSE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(SETUP_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(RE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(WILD_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(ENV_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(UTILS_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(EXE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(BUILTINS_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

clean:
	@make clean -C libft
	@echo "$(COLOUR_BLUE)libft object files cleaned$(COLOUR_END)"
	@rm -f $(OBJS)
	@echo "$(COLOUR_BLUE)object directory cleaned$(COLOUR_END)"

fclean: clean
	@rm -rf $(OBJS_DIR)
	@rm -f $(LIB)
	@echo "$(COLOUR_RED)libft.a removed$(COLOUR_END)"
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)$(NAME) removed$(COLOUR_END)"

re: fclean all

bonus: fclean all
