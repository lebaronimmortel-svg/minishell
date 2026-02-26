# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/20 11:16:51 by lukrodri          #+#    #+#              #
#    Updated: 2025/10/20 11:16:53 by lukrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strdup.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strlcpy.c ft_strlcat.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_printf.c ft_c.c ft_s.c ft_p.c ft_di.c ft_x.c ft_xx.c ft_u.c get_next_line.c get_next_line_utils.c
HEADER = libft.h
OBJS =	$(SRCS:.c=.o)
BONUS = $(BNS:.c=.o)
NAME = libft.a
AR = ar
MK = make
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm

all:$(NAME)

$(NAME) : $(OBJS) 
	$(AR) -rcs $(NAME) $(OBJS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

bonus : $(OBJS) $(BONUS)
	$(AR) rcs $(NAME) $(OBJS) $(BONUS)

fclean: clean
	$(RM) -f $(NAME)

clean:
	$(RM) -f $(OBJS) $(BONUS)

re:	fclean all

.PHONY: all fclean clean re bonus
