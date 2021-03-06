# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 19:04:13 by bemoreau          #+#    #+#              #
#    Updated: 2021/03/01 00:39:15 by bemoreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDE =	minishell.h\

INC_PATH = ./includes/

vpath %.c sources/builtins
vpath %.c sources/

FILES =		./sources/main\
			./sources/pipe\
			./sources/path\
			./sources/builtins/cd\
			./sources/builtins/cd_utils\
			./sources/builtins/pwd\
			./sources/builtins/env\
			./sources/builtins/export\
			./sources/builtins/unset\
			./sources/builtins/echo\
			./sources/builtins/exit\
			./sources/builtins/exit_utils\
			./sources/enter\
			./sources/parser\
			./sources/token\
			./sources/environment\
			./sources/expander\
			./sources/multi_pipe\
			./sources/redir\
			./sources/first_command\
			./sources/single_pipe\
			./sources/pipe_utils\
			./sources/init_pipe\
			./sources/redir_utils\
			./sources/gnl_prompt\
			./sources/builtins\
			./sources/middle_command\
			./sources/parser_utils\
			./sources/token_utils\
			./sources/expander_utils\
			./sources/lst_sort\
			./sources/prompt_malloc\
			./sources/backslash_quote\
			./sources/environment_utils\
			./sources/environment_manag\
			./sources/free\
			./sources/parser_save\
			./sources/environment_expander\
			./sources/lst_change\

SRCS = $(addsuffix .c, $(FILES))
OBJ = $(SRCS:.c=.o)

CC = gcc
L_CC = clang
LIB = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror

### COLORS ###

NOC = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
VIOLET = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m

all: 		LIBFT $(NAME)

LIBFT:
			@echo "$(CYAN)Building libft:$(NOC) $@"
			cd ./libft/ && make && cd ..

$(NAME): 	$(OBJ)
			@echo "$(CYAN)Constructing executable:$(NOC) $@"
			@$(L_CC) -g3 $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

.c.o:		${SRCS}
			@echo " $(VIOLET)[$(L_CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
			@$(L_CC) -g3 $(FLAGS) -c -I$(INC_PATH) $< -o ${<:.c=.o}
clean:
	@echo "$(CYAN)Clean libft:$(NOC) $@"
	@cd libft && make clean && cd ..
	@echo "\n$(RED)Removing '.o' objects: $(NOC) $@"
	@rm -f $(OBJ)

fclean: clean
	@echo "$(CYAN)Fclean libft:$(NOC) $@"
	@cd libft && make fclean && cd ..
	@echo "\n$(RED)Removing executable: $(NOC) $@"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean re fclean MLX LIBFT
