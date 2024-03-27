NAME = minishell
VERMILION_RED=\033[1;31m
AZURE_BLUE=\033[1;34m
GOLD_COLOR=\033[38;5;220m
GREEN=\033[0;32m
RESET=\033[0m
LIB_DIR = ./libft/
LIB_FILE = $(LIB_DIR)libft.a
SRC_FILES = srcs/main/main.c \
			srcs/main/init_parser.c \
			srcs/main/set_struct.c \
			srcs/main/signals.c \
			srcs/main/utils.c \
			srcs/main/wait_utils.c \
			srcs/parsing/first_checker.c \
			srcs/parsing/ft_get_prototype_list.c \
			srcs/parsing/get_env.c \
			srcs/parsing/heredoc_helper.c \
			srcs/parsing/open_heredoc.c \
			srcs/parsing/parse_path_utils.c \
			srcs/parsing/parse_path.c \
			srcs/parsing/parsing_errors_utils.c \
			srcs/parsing/parsing_errors.c \
			srcs/parsing/tokenizer_checker.c \
			srcs/parsing/tokenizer_getter.c \
			srcs/parsing/tokenizer_utils.c \
			srcs/parsing/tokenizer.c \
			srcs/expand/expand_get_values.c \
			srcs/expand/expand_heredoc.c \
			srcs/expand/expand_utils.c \
			srcs/expand/expand.c \
			srcs/execution/dup_and_close_normal.c \
			srcs/execution/exec_path.c \
			srcs/execution/exec.c \
			srcs/execution/execute_helper.c \
			srcs/execution/execute.c \
			srcs/execution/flush_and_epur.c \
			srcs/execution/free_handlers.c \
			srcs/execution/get_files.c \
			srcs/execution/get_size_to_send.c \
			srcs/execution/open_files.c \
			srcs/execution/redirections.c \
			srcs/builtins/cd/ft_cd.c \
			srcs/builtins/cd/go_home.c \
			srcs/builtins/cd/perror_cd.c \
			srcs/builtins/echo/ft_echo.c \
			srcs/builtins/env/ft_env.c \
			srcs/builtins/exit/exit_utils.c \
			srcs/builtins/exit/exit.c \
			srcs/builtins/export/export_utils.c \
			srcs/builtins/export/ft_export.c \
			srcs/builtins/pwd/ft_pwd.c \
			srcs/builtins/unset/ft_unset.c \
			srcs/free/free_main.c \
			srcs/free/free.c \

OBJECTS = $(SRC_FILES:.c=.o)
INCLUDE = minishell.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I -Ilibft 

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)  

$(LIB_FILE): 
	make -C $(LIB_DIR)

$(NAME) : $(LIB_FILE) $(OBJECTS) $(INCLUDE) Makefile
	@echo "$(GOLD_COLOR)Compiling Minishell...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) -g3 -Ilibft -lreadline $(OBJECTS) $(LIB_FILE)
	@echo "$(GOLD_COLOR)Minishell compiled ! :)$(RESET)"

clean:
	@echo "$(AZURE_BLUE)Cleaning in progress...$(RESET)"
	@rm -f $(OBJECTS)
	@make clean -sC $(LIB_DIR)
	@echo "$(AZURE_BLUE)Cleanup done ! :)$(RESET)"

fclean: clean
	@echo "$(AZURE_BLUE)Deep cleaning in progress...$(RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIB_DIR)
	@echo "$(AZURE_BLUE)Deep Cleaning over ! :)$(RESET)"	

re: fclean $(NAME)

.PHONY: all clean fclean re
