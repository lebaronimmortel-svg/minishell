NAME        = minishell

# --- Directories ---
SRC_DIR     = srcs
OBJ_DIR     = objs
LIBFT_DIR   = srcs/libft
HEADER_DIR  = header

# --- Files ---
SRC         = srcs/main/main.c srcs/main/main_loop.c \
              srcs/exec/exec.c srcs/exec/exec_error.c \
              srcs/exec/free_exec.c srcs/exec/redir.c \
              srcs/built_in/built_in.c srcs/built_in/echo.c \
              srcs/built_in/export.c srcs/built_in/unset.c \
              srcs/parser/expand.c srcs/parser/lexer.c \
              srcs/parser/parser.c srcs/utils/exec_utils.c \
              srcs/utils/exec_utils_bis.c \
              srcs/utils/exec_utils_fifth.c \
              srcs/utils/exec_utils_fourth.c \
              srcs/utils/exec_utils_third.c \
              srcs/utils/expand_utils.c \
              srcs/utils/export_utils.c \
              srcs/utils/free_exec_utils.c \
              srcs/utils/main_loop_utils.c \
              srcs/utils/redir_utils.c \
              srcs/utils/redir_utils_bis.c \
              srcs/utils/redir_utils_third.c \
              srcs/utils/utils.c \
              srcs/utils/utils_bis.c \
              srcs/utils/utils_third.c \
              srcs/utils/utils_third_bis.c \
              srcs/random/random1.c \
              srcs/random/random2.c \
              srcs/random/random3.c \
              srcs/random/random4.c \
              srcs/random/random5.c \
              srcs/random/random6.c \
              srcs/random/random7.c \
              srcs/random/random8.c \
              srcs/random/random9.c \
              srcs/random/random10.c \
              srcs/random/random11.c \
              srcs/random/random12.c \
              srcs/random/random13.c \
              srcs/random/random14.c \
              srcs/random/random15.c \
              srcs/random/random16.c \

OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)
HEADERS = header/typedef.h header/function.h header/header.h
LIBFT       = $(LIBFT_DIR)/libft.a

# --- Compilation ---
CC          = cc
FLAGS       = -Wall -Wextra -Werror -g
RM          = rm -rf

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

# Create objs/ directories automatically
$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I $(HEADER_DIR) -I $(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
