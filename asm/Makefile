# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/11 18:14:04 by tvisenti          #+#    #+#              #
#    Updated: 2016/08/29 14:42:09 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = asm

SRC_PATH = ./src
LIB_PATH = ./lib
INC_PATH = ./inc
OBJ_PATH = ./obj
OBJLIB_PATH = ./obj

SRC_NAME =	asm_main.c\
			asm_parsing.c\
			asm_copy_header.c\
			asm_binary_writer.c\
			asm_check_arg.c\
			asm_check_instruction.c\
			asm_check_label.c\
			asm_parse_instruct.c\
			asm_write_octal.c\
			asm_writer.c\

LIB_NAME =	asm_init.c\
			asm_error.c\
			asm_free.c\

INC_NAME =	asm.h\

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJLIB_NAME = $(LIB_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJLIB = $(addprefix $(OBJLIB_PATH)/,$(OBJLIB_NAME))

all: $(NAME)

$(NAME): $(OBJ) $(OBJLIB)
	@echo ""
	@make -C ../libft
	@$(CC) $(FLAGS) -o $@ $^ ../libft/libft.a ../libft/ft_printf/libftprintf.a
	@echo "\033[1;34mASM\t\t\033[1;33mCompilation\t\033[0;32m[OK]\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $<
	@printf "\033[42m \033[0m"

$(OBJLIB_PATH)/%.o: $(LIB_PATH)/%.c
	@mkdir $(OBJLIB_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) -o $@ -c $<
	@printf "\033[42m \033[0m"

clean:
	@rm -rf $(OBJ) $(OBJLIB)
	@cd ../libft && $(MAKE) clean
	@cd ../libft/ft_printf && $(MAKE) clean
	@echo "\033[1;34mASM\t\t\033[1;33mCleaning obj\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -rf ./obj $(NAME)
	@cd ../libft && $(MAKE) fclean
	@cd ../libft/ft_printf && $(MAKE) fclean
	@echo "\033[1;34mASM\t\t\033[1;33mCleaning lib\t\033[0;32m[OK]\033[0m"

re: fclean all

norme:
	@norminette $(SRC) $(LIB) $(INC)
	@echo "\033[1;34mASM\t\t\033[1;33mNorminette\t\033[0;32m[OK]\033[0m"
