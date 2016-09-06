# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/29 14:17:38 by tvisenti          #+#    #+#              #
#    Updated: 2016/08/29 14:54:47 by tvisenti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C ./asm
	@make -C ./vm

clean:
	@make clean -C ./asm
	@make clean -C ./vm

fclean:
	@make fclean -C ./asm
	@make fclean -C ./vm

re:
	@make re -C ./asm
	@make re -C ./vm

norme:
	@make norme -C ./asm
	@make norme -C ./vm

.PHONY: all clean fclean re norme
