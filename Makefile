# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngharian <ngharian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 15:12:03 by gdero             #+#    #+#              #
#    Updated: 2024/12/16 13:03:40 by ngharian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = minishell.c \
		./parsing/parsing.c \
		./parsing/pipe_parse.c \
		./parsing/arrow_parse.c \
		./parsing/heredoc.c \
		./parsing/expander.c \
		./parsing/expander_utils.c \
		./parsing/pipe_join.c \
		./parsing/find_eof_heredoc.c \
		./builtin/builtin.c \
		./builtin/cd.c \
		./builtin/echo.c \
		./builtin/env.c \
		./builtin/exit.c \
		./builtin/export.c \
		./builtin/export_utils.c \
		./builtin/export_utils2.c \
		./builtin/pwd.c \
		./builtin/unset.c \
		update_cwd.c \
		free.c \
		split_minishell.c \
		commands.c \
		del_quotes.c \
		redirection.c \
		redirection_utils.c \
		execution.c \
		execution_utils.c \
		signaux.c \
		signaux_utils.c

OBJECTS = $(SRCS:.c=.o)

HEADER = minishell.h
NAME = minishell
CFLAGS = -g -Wall -Wextra -Werror
CC = gcc
RM = rm -f
MAKE_LIBFT = make -s -C ./Libft
LIBFT = ./Libft/libft.a

$(NAME): msg $(OBJECTS)
	@printf "\033[K\033[0;34mBeast compiled.\n"
	@$(MAKE_LIBFT)
	@$(CC) $(CFLAGS) ${OBJECTS} ${LIBFT} -I ${HEADER}  -o ${NAME} -lreadline
	@printf "\r\033[0;31mThe Beast is ready.\033[0m\n"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@sleep 0.001
	@printf "\033[K\033[0;32mCompiling the Beast... : \033[0;33m%s\r" "$<"
	
all: $(NAME)

msg:
	@printf "\033[K\033[0;31mThe Beast has been awoken.\n"
	@sleep 2
	
clean:
	@$(MAKE_LIBFT) clean
	@$(RM) $(OBJECTS)
	@sleep 0.5
	@printf "\033[0;32mEverything is clean.\033[0m\n"

fclean: clean
	@$(MAKE_LIBFT) fclean
	@$(RM) $(NAME)
	@sleep 1
	@printf "\033[0;31mBeast destroyed.\033[0m\n"

re: fclean all

.PHONY: all clean fclean re msg