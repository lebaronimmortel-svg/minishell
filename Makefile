# ================= CONFIG =================
NAME    	= minishell
CC      	= cc
CFLAGS  	= -Wall -Wextra -Werror
LIBFTDIR 	= ./srcs/libft
LIBFT 		= $(LIBFTDIR)/libft.a
SRC     	= srcs/main.c srcs/utils/exec.c srcs/utils/print_header.c
OBJ     	= $(SRC:.c=.o)
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
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) || { \
		printf "$(RED)✖ Compilation failure !$(RESET)\n"; \
		exit 1; }
	@printf "\n$(GREEN)✔ Compilation success !$(RESET)\n\n"
	@printf "\a"
	
$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) --no-print-directory

%.o: %.c
	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@PERCENT=$$(echo $$(($(COUNT)*100/$(TOTAL)))); \
	BAR_WIDTH=40; \
	FILLED=$$(echo $$(($(COUNT)*BAR_WIDTH/$(TOTAL)))); \
	EMPTY=$$(echo $$((BAR_WIDTH-FILLED))); \
	printf "\r$(MAGENTA)⟦Compiling MINISHELL⟧	$(CYAN)["; \
	printf "%0.s▓" $$(seq 1 $$FILLED); \
	printf "%0.s░" $$(seq 1 $$EMPTY); \
	printf "] $(MAGENTA)%3d%%$(RESET)" $$PERCENT; \
	$(CC) $(CFLAGS) -c $< -o $@

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
	@rm -f $(OBJ)
	@rm -rf objs
	@$(MAKE) clean -C $(LIBFTDIR) --no-print-directory
	@printf "$(MAGENTA)♻ Cleanup successful$(RESET)\n"

fclean: clean
	@printf "$(WHITE)"
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@printf "$(MAGENTA)♻ Executable removed$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re banner

