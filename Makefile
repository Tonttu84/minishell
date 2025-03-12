# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 13:14:15 by jtuomi            #+#    #+#              #
#    Updated: 2025/03/11 20:10:01 by jtuomi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR = ar rcs
CC = cc
INCLUDE_DIRS = libft
CFLAGS = -Wall -Wextra -Werror -g2 -DUSER=\"$(USER)\"

SRC = lexer.c	ft_xcalloc.c parsing_utils.c heredocs.c init_utils.c\
	exit.c	env.c utils.c page.c rem_quotes.c test.c open.c signal.c \
	main.c create_list.c ft_lstaddback.c	input.c	export.c redir.c \
	redirect.c exec.c path.c
SRC := $(addprefix srcs/, $(SRC))
DEBUG = debug.c
DEBUG := $(addprefix srcs/debug/, $(DEBUG))
DEBUG_OBJ := $(DEBUG:%.c=%.o)
OBJ := $(SRC:%.c=%.o)
MAKE = make -C
NAME = minishell
LIBFT = ./libft/libft.a

all: debug $(NAME)
$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(DEBUG_OBJ) -L $(INCLUDE_DIRS) -lft -lreadline
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
debug: $(DEBUG_OBJ)
.PHONY:
	all, libft, clean, fclean, re, debug
