NAME = libft.a

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c get_next_line_utils.c

BONUS = ft_lstadd_front_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstclear_bonus.c

BONUSO = ft_lstadd_front_bonus.o ft_lstnew_bonus.o ft_lstsize_bonus.o ft_lstlast_bonus.o ft_lstadd_back_bonus.o ft_lstdelone_bonus.o ft_lstiter_bonus.o ft_lstmap_bonus.o ft_lstclear_bonus.o

SRCO = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strcmp.o ft_strncmp.o ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o get_next_line.o get_next_line_utils.o

all:	$(NAME)

$(NAME):
	@cc -Wall -Werror -Wextra -c $(SRC)
	@ar rc $(NAME) $(SRCO)
	@ranlib $(NAME)

clean:
	@/bin/rm -rf $(SRCO) $(BONUSO)

fclean:
	@/bin/rm -rf $(NAME) $(SRCO) $(BONUSO)

re: fclean all

bonus:	$(BONUSO)

$(BONUSO):
	@cc -Wall -Werror -Wextra -c $(BONUS)
	@ar rc $(NAME) $(BONUSO)
	@ranlib $(NAME)

.PHONY: bonus all clean fclean re
