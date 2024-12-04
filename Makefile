SRCS = minishell.c \
		./parsing/parsing.c \
		./parsing/pipe_parse.c \
		./parsing/arrow_parse.c \
		./parsing/heredoc.c \
		./parsing/expander.c \
		./parsing/pipe_join.c \
		./parsing/find_eof_heredoc.c \
		./builtin/builtin.c \
		./builtin/cd.c \
		./builtin/cd2.c \
		./builtin/echo.c \
		./builtin/env.c \
		./builtin/exit.c \
		./builtin/export.c \
		./builtin/export2.c \
		./builtin/pwd.c \
		./builtin/unset.c \
		signaux.c \
		free.c \
		split_minishell.c \
		commands.c \
		del_quotes.c \
		redirection.c \
		redirection_utils.c \
		execution.c 

OBJECTS = $(SRCS:.c=.o)

HEADER = minishell.h
NAME = minishell
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
CC = gcc
RM = rm -f
MAKE_LIBFT = make -s -C ./libft
LIBFT = ./Libft/libft.a

$(NAME): $(OBJECTS)
	$(MAKE_LIBFT)
	$(CC) $(CFLAGS) ${OBJECTS} ${LIBFT} -I ${HEADER}  -o ${NAME} -lreadline -L /Users/ngharian/homebrew/Cellar/readline/8.2.13/lib -I /Users/ngharian/homebrew/Cellar/readline/8.2.13/include
	#/Users/gdero/.brew/opt/readline/lib -I /Users/gdero/.brew/opt/readline/include
	#/Users/ngharian/homebrew/Cellar/readline/8.2.13/lib -I /Users/ngharian/homebrew/Cellar/readline/8.2.13/include

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	
all: $(NAME)

clean:
	$(MAKE_LIBFT) clean
	$(RM) $(OBJECTS)

fclean: clean
	$(MAKE_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
