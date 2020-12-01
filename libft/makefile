# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 18:12:36 by psemsari          #+#    #+#              #
#    Updated: 2020/12/01 09:49:43 by bemoreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = libft.a

OBJ_DIR = obj

CFLAGS = -Wall -Werror -Wextra -g

IFLAGS = -I$(INCLUDES)

SRC = ft_strlen.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strdup.c \
	ft_calloc.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_itoa.c \
	ft_nbdigit.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strtrim.c \
	ft_split.c \
	ft_strmapi.c \
	ft_putnstr.c \
	ft_putrep.c \
	ft_putunbr.c \
	ft_unbdigit.c \
	ft_itouhex.c \
	ft_lltohex.c \
	ft_nbdigit16.c \
	ft_nbdigitll16.c \
	ft_strljoin.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	get_next_line.c \
	ft_strrem.c \
	ft_atoui.c \
	ft_strjoin_c.c \
	ft_strafter.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

INCLUDES = ../../includes

$(OBJ_DIR)/%.o : %.c
					@mkdir -p $(OBJ_DIR)
					@$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@ -g

all: $(NAME)

$(NAME): $(OBJ)
					@ar rcs $(NAME) $(OBJ)

clean:
					@rm -rf $(OBJ_DIR)

fclean: clean
					@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
