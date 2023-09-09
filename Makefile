# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/03 20:58:45 by vvagapov          #+#    #+#              #
#    Updated: 2023/09/09 21:36:27 by vvagapov         ###   ########.fr        #
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
UTILS_DIR = utilities/
OBJS_DIR = obj/
EXE_DIR = execute/
BUILTINS_DIR = built-ins/

#Sources by folder
_CORE := main.c process_line.c
_TOKENIZE := clean_token_list.c tokenize.c redirections_filenames.c
_PARSE := parse.c preliminary_syntax_checks.c \
		form_tree.c syntax_checking.c \
		tree_execution.c form_pipeline.c
_SETUP := set_data.c set_input_mode.c signal_handlers.c
_REDIR := redirections.c heredoc.c heredoc_signals.c go_through_heredocs.c
_ENV := environment_tools.c
_UTILS := array_utils.c list_utils.c character_utils.c \
		tokenizing_utils.c debug_utils.c ast_utils.c \
		exiting.c errors.c cleaners.c
_EXE := piping.c pipes_utils.c
_BUILTINS := cd.c echo.c env.c exit.c export.c pwd.c unset.c

ALL_SRCS := $(addprefix $(CORE_DIR), $(_CORE)) \
			$(addprefix $(TOKENIZE_DIR), $(_TOKENIZE)) \
			$(addprefix $(PARSE_DIR), $(_PARSE)) \
			$(addprefix $(SETUP_DIR), $(_SETUP)) \
			$(addprefix $(RE_DIR), $(_REDIR)) \
			$(addprefix $(ENV_DIR), $(_ENV)) \
			$(addprefix $(UTILS_DIR), $(_UTILS)) \
			$(addprefix $(EXE_DIR), $(_EXE)) \
			$(addprefix $(BUILTINS_DIR), $(_BUILTINS))

SRCS = $(_CORE) $(_TOKENIZE) $(_PARSE) $(_SETUP) $(_REDIR) $(_ENV) $(_UTILS) $(_EXE) $(_BUILTINS)
OBJ_FILES = $(SRCS:.c=.o)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(SRCS:.c=.o))

LIB = libft/libft.a

all: $(NAME)

$(LIB):
	@make all -C libft
	@make bonus -C libft
	@echo "$(COLOUR_GREEN)libft compilation completed$(COLOUR_END)"

$(NAME): $(LIB) $(OBJS_DIR) $(OBJS)
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
