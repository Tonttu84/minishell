# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 13:14:15 by jtuomi            #+#    #+#              #
#    Updated: 2025/02/16 18:51:29 by jtuomi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR = ar rcs
CC = cc
INCLUDE_DIRS = libft
CFLAGS = -Wall -Wextra -Werror -g2
SRC = lexer.c	ft_xcalloc.c\
	exit.c \
	main.c
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
	$(MAKE) libft all supp
clean:
	$(MAKE) libft clean
	rm -f $(OBJ)
fclean: clean
	$(MAKE) libft fclean
	rm -f $(NAME)
re: fclean all

.PHONY:
	all, libft, clean, flean, re
