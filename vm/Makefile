# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/25 10:18:16 by ademenet          #+#    #+#              #
#    Updated: 2016/08/31 16:52:50 by ademenet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror
DFLAGS = -g -ggdb

NAME = corewar

SRC_PATH = ./src
OBJ_PATH = ./obj
INC_PATH = ./inc/
LIB_PATH = ../libft/

INC_PATH_L = $(LIB_PATH)
INC_PATH_P = $(LIB_PATH)/ft_printf/include/

SRC_NAME =	cw_ins_add.c\
			cw_ins_aff.c\
			cw_ins_and.c\
			cw_ins_fork.c\
			cw_ins_ld.c\
			cw_ins_ldi.c\
			cw_ins_lfork.c\
			cw_ins_live.c\
			cw_ins_lld.c\
			cw_ins_lldi.c\
			cw_ins_or.c\
			cw_ins_st.c\
			cw_ins_sti.c\
			cw_ins_sub.c\
			cw_ins_tools.c\
			cw_ins_xor.c\
			cw_ins_zjmp.c\
			cw_processor_cycles.c\
			cw_processor_inits.c\
			cw_processor.c\
			cw_vizualizer_inits.c\
			cw_vizualizer_proc.c\
			cw_vizualizer_print.c\
			cw_main.c\
			cw_param_handler.c\
			cw_champion_creation.c\
			cw_manage_list.c\
			cw_manage_list_advanced.c\
			cw_load_instructions.c\
			cw_ins_get_data.c\
			cw_tools.c\
			cw_bonus_handler.c\
			cw_bonus_debug.c

INC_NAME = corewar.h

CURSE = -lpanel -lncurses

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@echo ""
	@make -C ../libft
	@$(CC) $(FLAGS) $(DFLAGS) $(CURSE) -o $@ $^ -I$(INC_PATH) -I $(LIB_PATH) -I $(INC_PATH_P) ../libft/libft.a ../libft/ft_printf/libftprintf.a
	@echo "\033[1;34mCorewar\t\t\033[1;33mCompilation\t\033[0;32m[OK]\033[0m"
	@say -v 'Trinoids' "Welcome to... Corewar"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(DFLAGS) -c -o $@ $<
	@printf "\033[42m \033[0m"

clean:
	@make clean -C ../libft
	@rm -rf ./obj
	@echo "\033[1;34mCorewar\t\t\033[1;33mCleaning obj\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make fclean -C ../libft
	@rm -rf $(NAME)
	@echo "\033[1;34mCorewar\t\t\033[1;33mCleaning lib\t\033[0;32m[OK]\033[0m"

re: fclean all

norme:
	@norminette */*[hc]
	@echo "\033[1;34mCorewar\t\033[1;33mNorme\t\033[0;32m[OK]\033[0m"

.PHONY: all clean fclean re norme
