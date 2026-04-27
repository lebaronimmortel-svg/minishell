# ================= CONFIG =================
NAME    	= minishell
CC      	= cc
CFLAGS  	= -Wall -Wextra -Werror
LIBFTDIR 	= ./srcs/libft
LIBFT 		= $(LIBFTDIR)/libft.a

SRC     	= srcs/main/main.c srcs/parser/lexer.c\
			  srcs/parser/parser.c srcs/utils/utils.c\
			  srcs/utils/utils_bis.c srcs/exec/exec.c\
			  srcs/exec/free_exec.c srcs/utils/free_exec_utils.c\
			  srcs/utils/exec_utils.c srcs/utils/utils_third_bis.c\
			  srcs/exec/exec_error.c srcs/exec/redir.c\
			  srcs/utils/redir_utils.c srcs/utils/redir_utils_bis.c\
			  srcs/utils/redir_utils_third.c srcs/utils/exec_utils_fourth.c\
			  srcs/utils/exec_utils_fifth.c\
			  srcs/utils/exec_utils_bis.c srcs/utils/exec_utils_third.c\
			  srcs/utils/export_utils.c srcs/utils/utils_third.c\
			  srcs/main/main_loop.c srcs/utils/expand_utils.c\
			  srcs/utils/main_loop_utils.c srcs/parser/expand.c\
			  srcs/built_in/built_in.c srcs/built_in/echo.c\
			  srcs/built_in/export.c srcs/built_in/unset.c

OBJDIR  	= objs
OBJ     	= $(SRC:%.c=$(OBJDIR)/%.o)

TOTAL   	:= $(words $(SRC))
COUNT   	:= 0

# ================= COLORS =================
RESET   = \033[0m
BOLD    = \033[1m
RED     = \033[31m
GREEN   = \033[32m
CYAN    = \033[36m
MAGENTA = \033[35m
WHITE	= \033[37m

# ================= RULES =================
all: banner $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline || { \
		printf "$(RED)✖ Compilation failure !$(RESET)\n"; \
		exit 1; }
	@printf "\n$(GREEN)✔ Compilation success !$(RESET)\n\n"
	@printf "\a"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) --no-print-directory

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@PERCENT=$$(echo $$(($(COUNT)*100/$(TOTAL)))); \
	BAR_WIDTH=40; \
	FILLED=$$(echo $$(($(COUNT)*BAR_WIDTH/$(TOTAL)))); \
	EMPTY=$$(echo $$((BAR_WIDTH-FILLED))); \
	printf "\r$(MAGENTA)⟦Compiling MINISHELL⟧	$(CYAN)["; \
	printf "%0.s▓" $$(seq 1 $$FILLED); \
	printf "%0.s░" $$(seq 1 $$EMPTY); \
	printf "] $(MAGENTA)%3d%%$(RESET)" $$PERCENT; \
	$(CC) $(CFLAGS) -c $< -o $@ -g

banner:
	@clear
	@printf "$(CYAN)$(BOLD)\n"
	@printf "██████╗ ██╗   ██╗██╗██╗     ██████╗ \n"
	@printf "██╔══██╗██║   ██║██║██║     ██╔══██╗\n"
	@printf "██████╔╝██║   ██║██║██║     ██║  ██║\n"
	@printf "██╔══██╗██║   ██║██║██║     ██║  ██║\n"
	@printf "██████╔╝╚██████╔╝██║███████╗██████╔╝\n"
	@printf "╚═════╝  ╚═════╝ ╚═╝╚══════╝╚═════╝ \n"
	@printf "$(RESET)\n"
	@sleep 0.5

clean:
	@printf "$(WHITE)"
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C $(LIBFTDIR) --no-print-directory
	@printf "$(MAGENTA)♻ Cleanup successful$(RESET)\n"

fclean: clean
	@printf "$(WHITE)"
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@printf "$(MAGENTA)♻ Executable removed$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re banner
