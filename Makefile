#Target Binary Program
NAME = minishell

#Color scheme
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Flags
FLAGS = -Wall -Werror -Wextra -I includes
READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

#Direcory locations
CORE_DIR = core/
PARSE_DIR = parsing/
SETUP_DIR = setup/
UTILS_DIR = utilities/
OBJS_DIR = obj/

#Sources by folder
_CORE := main.c process_line.c
_PARSE := parse.c tokenize.c clean_token_list.c \
		redirections_filenames.c preliminary_syntax_checks.c \
		#syntax_checking.c and_or_list_syntax_rules.c \
		#job_and_words_syntax_rules.c \

_SETUP := set_data.c set_input_mode.c signal_handlers.c
_UTILS := array_utils.c exiting.c errors.c \
		cleaners.c character_utils.c tokenizing_utils.c \
		debug_utils.c \
		#ast_utils.c

ALL_SRCS := $(addprefix $(CORE_DIR), $(_CORE)) \
			$(addprefix $(PARSE_DIR), $(_PARSE)) \
			$(addprefix $(SETUP_DIR), $(_SETUP)) \
			$(addprefix $(UTILS_DIR), $(_UTILS))

SRCS = $(_CORE) $(_PARSE) $(_SETUP) $(_UTILS)
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

$(OBJS_DIR)%.o: $(PARSE_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(SETUP_DIR)%.c
	@cc $(FLAGS) -c $< -o $@ 
	@echo "$(COLOUR_BLUE)$@ created$(COLOUR_END)"

$(OBJS_DIR)%.o: $(UTILS_DIR)%.c
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
