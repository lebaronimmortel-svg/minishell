# ================= CONFIG =================
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strdup.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strlcpy.c ft_strlcat.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_printf.c ft_c.c ft_s.c ft_p.c ft_di.c ft_x.c ft_xx.c ft_u.c get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
NAME = libft.a
AR = ar rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

TOTAL := $(words $(SRCS))

# ================= COLORS =================
RESET   = \033[0m
CYAN    = \033[36m
MAGENTA = \033[35m

# ================= RULES =================
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo ""

%.o: %.c
	@# Calculer barre avant compilation
	@COUNT=$$(($(shell echo $$(($(shell ls -1 $(OBJS) 2>/dev/null | wc -l)+1))))); \
	PERCENT=$$(($$COUNT*100/$(TOTAL))); \
	BAR_WIDTH=40; \
	FILLED=$$((BAR_WIDTH*$$COUNT/$(TOTAL))); \
	EMPTY=$$((BAR_WIDTH-FILLED)); \
	printf "\r$(MAGENTA)⟦Compiling LIBFT⟧	$(CYAN)["; \
	printf "%0.s▓" $$(seq 1 $$FILLED); \
	printf "%0.s░" $$(seq 1 $$EMPTY); \
	printf "] $(MAGENTA)%3d%%$(RESET)" $$PERCENT; \
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

