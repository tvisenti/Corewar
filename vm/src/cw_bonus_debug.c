/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_bonus_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 16:01:21 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 12:00:13 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void		cw_bonus_db_twoparams(t_proc *proc, t_p *tmp, t_ocp *ocp,
			int p[2])
{
	ft_printf("P%5d | %s ", tmp->id, g_op[tmp->opcode - 1].name);
	if (ocp->first == REG_CODE)
		ft_printf("r%d ", p[0]);
	else
		ft_printf("%d ", p[0]);
	if (ocp->second == REG_CODE)
		ft_printf("r%d\n", p[1]);
	else
		ft_printf("%d\n", p[1]);
}

/*
** Dump la mémoire zaz-like !
*/

int			cw_dump_display_zazlike(t_proc *proc)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0)
			ft_printf("0x%04x : ", i);
		if (i != 0)
			i % 64 == 0 ? ft_printf("\n0x%04x : ", i) : ft_printf(" ");
		ft_printf("%.2hhx", proc->mem[i]);
		i++;
	}
	return (0);
}
