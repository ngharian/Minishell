# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdero <gdero@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 13:47:07 by gdero             #+#    #+#              #
#    Updated: 2024/10/08 16:19:38 by gdero            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isprint.c \
	   ft_isascii.c \
	   ft_strlen.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_strncmp.c \
	   ft_memcmp.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_strlcpy.c \
	   ft_atoi.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_strlcat.c \
	   ft_strnstr.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strtrim.c \
	   ft_striteri.c \
	   ft_strmapi.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putnbr_fd.c \
	   ft_putendl_fd.c \
	   get_next_line.c \
	   get_next_line_utils.c

OBJECTS = $(SRCS:.c=.o)
BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJBONUS = $(BONUS:.c=.o)
HEADER = libft.h
NAME = libft.a
LIBCREATE = ar -rc
LIBUPDATE = ranlib
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f


.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} -I $(HEADER)
$(NAME): $(OBJECTS)
	$(LIBCREATE) $(NAME) $(OBJECTS)
	$(LIBUPDATE) $(NAME)

bonus: $(OBJBONUS)
	$(LIBCREATE) $(NAME) $(OBJBONUS)
	$(LIBUPDATE) $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJECTS) $(OBJBONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
