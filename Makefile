SRCS = minishell.c \
		./parsing/parsing.c \
		./parsing/pipe_parse.c \
		./parsing/arrow_parse.c \
		./parsing/heredoc.c \
		./parsing/expander.c \
		./parsing/pipe_join.c \
		./builtin/builtin.c \
		./builtin/cd.c \
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
		in_outfiles.c \
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
	$(CC) $(CFLAGS) ${OBJECTS} ${LIBFT} -I ${HEADER}  -o ${NAME} -lreadline -L /Users/gdero/.brew/opt/readline/lib -I /Users/gdero/.brew/opt/readline/include

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
