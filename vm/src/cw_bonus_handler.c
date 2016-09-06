/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_bonus_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 10:34:15 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/30 10:46:30 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
**	Pour ajouter la gestion d'une option, ajouter la lettre choisie dans la
**	string de ft_cinstr
*/

void	cw_bon_handler(char **av, int ac, int param)
{
	arr_set(g_bon, 0, 128);
	while (param < ac)
	{
		if (av[param][0] == '-' && ft_cinstr(param[av][1], "vdzcms"))
			g_bon[(unsigned char)av[param][1]] = 1;
		else
		{
			cw_error_msg("Wrong option format");
			ft_printf("%sOptions available :\n", GRE);
			ft_printf("-v : nCurse visualiser\n");
			ft_printf("-d : debug mode\n");
			ft_printf("-c : display cycles\n");
			ft_printf("-s : play beep when process is killed\n");
			ft_printf("-z : dump zaz-like (use with dump option)\n");
			ft_printf("-m : mute live messages%s\n", EOC);
			exit(1);
		}
		param++;
	}
	if (g_bon['d'] || g_bon['z'] || g_bon['c'])
		g_bon['v'] = 0;
}
