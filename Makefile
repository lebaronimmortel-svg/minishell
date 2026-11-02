NAME        = minishell

# --- Directories ---
SRC_DIR     = srcs
OBJ_DIR     = objs
LIBFT_DIR   = srcs/libft
HEADER_DIR  = header

# --- Files ---
SRC         = srcs/main/main.c \
              srcs/main/finish_program.c \
              srcs/main/prompt_loop.c \
              srcs/exec/exec_prompt.c \
              srcs/exec/exec.c \
              srcs/exec/exec_built_in.c \
              srcs/exec/exec_built_in_utils.c \
              srcs/exec/exec_cmd.c \
              srcs/exec/exec_cmd_utils.c \
              srcs/exec/exec_error.c \
              srcs/exec/free_exec.c \
              srcs/exec/free_exec_utils.c \
              srcs/exec/process_exec.c \
              srcs/exec/status_code.c \
              srcs/built_in/built_in.c \
              srcs/built_in/built_in_utils.c \
              srcs/built_in/cd_utils.c \
              srcs/built_in/change_path.c \
              srcs/built_in/echo.c \
              srcs/built_in/echo_utils.c \
              srcs/built_in/export.c \
              srcs/built_in/export_add.c \
              srcs/built_in/export_utils.c \
              srcs/built_in/replace_env_var.c \
              srcs/built_in/unset.c \
              srcs/parser/check_quote.c \
              srcs/parser/check_quote_utils.c \
              srcs/parser/expand.c \
              srcs/parser/expand_utils.c \
              srcs/parser/get_pid.c \
              srcs/parser/handle_spaces.c \
              srcs/parser/lexer.c \
              srcs/parser/parser.c \
              srcs/redir/expand_heredoc.c \
              srcs/redir/handle_heredoc.c \
              srcs/redir/handle_redir.c \
              srcs/redir/heredoc.c \
              srcs/redir/infile_redir.c \
              srcs/redir/redir.c \
              srcs/redir/skip_redir.c \
              srcs/utils/find_env.c \
              srcs/utils/get_path.c \
              srcs/utils/remove_quote.c \
              srcs/utils/set_signal.c \
              srcs/utils/split_dup.c \
              srcs/utils/heredoc_utils.c \


OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)
HEADERS = header/typedef.h header/function.h header/header.h
LIBFT       = $(LIBFT_DIR)/libft.a
CC          = cc
FLAGS       = -Wall -Wextra -Werror -g
RM          = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

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
