# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 13:51:13 by lukrodri          #+#    #+#              #
#    Updated: 2026/01/13 10:08:42 by lukrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCDIR = srcs
UTLDIR = srcs/utils
OBJDIR = objs
LIBFTDIR = $(SRCDIR)/libft
LIBFT = $(LIBFTDIR)/libft.a

VPATH = $(SRCDIR) $(UTLDIR)

SRC = main.c
UTL = 

OBJ = \
	$(addprefix $(OBJDIR)/, $(SRC:.c=.o)) \
	$(addprefix $(OBJDIR)/, $(UTL:.c=.o))

HEADERS = header/header.h

CC = cc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $^ -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(OBJDIR)/%.o: %.c $(HEADERS)
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re

