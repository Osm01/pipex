NAME:= pipex
NAME_B:= pipex_bonus
CC = cc
CFLAGS:= -Wall -Wextra -Werror #-fsanitize=address -g3
SRC:= pipex.c pipex_helper.c ft_split.c ft_strncmp.c ft_strjoin.c ft_substr.c ft_strlen.c ft_strdup.c ft_strcmp.c \
get_next_line.c ft_strchr.c ft_strjoin_for_get_next_line.c
bonus:= pipex_bonus.c pipex_helper.c ft_split.c ft_strncmp.c ft_strjoin.c ft_substr.c ft_strlen.c ft_strdup.c \
ft_strcmp.c get_next_line.c ft_strchr.c ft_strjoin_for_get_next_line.c
OBJ_SRC:= $(SRC:.c=.o)
OBJ_BONUS:= $(bonus:.c=.o)
all: $(NAME)
$(NAME): $(OBJ_SRC)
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $(NAME)
bonus: $(NAME_B)

$(NAME_B): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_B)
clean:
	rm -f $(OBJ_SRC) $(OBJ_BONUS)
fclean: clean
	rm -f $(NAME) $(NAME_B)
re: fclean all bonus
.PHONY:	 all clean fclean re bonus