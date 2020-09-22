# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 19:04:13 by bemoreau          #+#    #+#              #
#    Updated: 2020/07/06 23:10:44 by mdavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDE =	minishell.h\

INC_PATH = ./includes/

vpath %.c sources/parsing

FILES =		./sources/main\
			./sources/path\

BIN =		./bin/cd\
			./bin/echo\
			./bin/env\
			./bin/pwd\
			./bin/exit\

SRCS = $(addsuffix .c, $(FILES))
OBJ = $(SRCS:.c=.o)
BUILTINS = $(BIN:%.c=%)

CC = gcc
L_CC = clang
LIB = ./libft/libft.a
#FLAGS = -Wall -Wextra -Werror

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
			cd libft && make && cd ..

$(NAME): 	$(OBJ) $(BUILTINS)
			@echo "$(CYAN)Constructing executable:$(NOC) $@"
			@$(L_CC) -g3 $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

$(BIN): %: %.c
			@echo " $(VIOLET)[$(L_CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
			@$(L_CC) -g3 $(FLAGS) $< -o ${<:%.c=%} $(LIB)

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

.PHONY: all clean re fclean MLX