# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschweit <bschweit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 17:56:14 by cdescour          #+#    #+#              #
#    Updated: 2022/12/02 17:03:46 by bschweit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binary
NAME = minishell
# Path
SRC_PATH = srcs/
OBJ_PATH = objs/
CPPFLAGS = -I./includes/
# Name
SRC_NAME =	main.c 		\
			init.c		\
			prompt.c	\
			utility.c	\
			print_env.c	\
			parsing.c \
			checker.c \
			lexer.c \
			builtin_checker.c \
			variable.c \
			exec.c\
			echo.c \
			export.c unset.c
	
	
OBJ_NAME = $(SRC_NAME:.c=.o)
# Files
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
# Flags
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Rules

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[34mCreation of $(NAME) ...\033[0m"
	@$(CC) $(OBJ) -o $@ -lreadline
	@echo "\033[32m$(NAME) created\n\033[0m"
	@echo "\033[33mEND: everything is complete.\033[0m"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -o $@ -c $<

clean:
	@echo "\033[33mRemoval of .o files of $(NAME) ...\033[0m"
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[31mFiles .o deleted\n\033[0m"
	
fclean: clean
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all

r: all
	@clear && ./minishell

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h

.PHONY: all, clean, fclean, re, norme
