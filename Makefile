# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 13:14:15 by jtuomi            #+#    #+#              #
#    Updated: 2025/02/19 22:04:42 by jtuomi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR = ar rcs
CC = cc
INCLUDE_DIRS = libft
CFLAGS = -Wall -Wextra -Werror -g2
SRC = main.c lexer.c \
	exit.c	env.c utils.c \
	create_list.c ft_lstaddback.c \
	ft_xcalloc.c
SRC := $(addprefix srcs/, $(SRC))
OBJ := $(SRC:%.c=%.o)
MAKE = make -C
NAME = minishell
LIBFT = ./libft/libft.a

all: $(NAME)
$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L $(INCLUDE_DIRS) -lft
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
$(LIBFT):
	$(MAKE) libft all supp bonus
clean:
	$(MAKE) libft clean
	rm -f $(OBJ)
fclean: clean
	$(MAKE) libft fclean
	rm -f $(NAME)
re: fclean all

.PHONY:
	all, libft, clean, flean, re
