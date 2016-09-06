/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/29 09:24:29 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	asm_init_global(void)
{
	g_line = 0;
	g_pos = 0;
	g_temp = 0;
}

int		asm_argc_check(int argc)
{
	if (argc == 2)
		ft_printf("Put one champion, please !\n");
	return (1);
}

int		main(int argc, char **argv)
{
	t_header	*head;
	int			index;
	int			check;

	index = 1;
	check = 0;
	head = NULL;
	asm_init_global();
	if (argc > 1)
	{
		if (argv[index][0] == '-' && argv[index][1] == 'b' && ++index)
			check = asm_argc_check(argc);
		while (index < argc)
		{
			head = asm_header_init();
			if (asm_parsing(argv[index++], head, check) == -1)
				ft_printf("Put one valid champion, please !\n");
			free(head);
			head = NULL;
			asm_init_global();
		}
	}
	else
		ft_printf("Put one champion, please !\n");
	return (0);
}
