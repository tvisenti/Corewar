/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 14:49:48 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 12:13:30 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction prend 3 registres en paramètre, additionne le contenu des
** 2 premiers et met le résultat dans le troisième. Cette opération modifie
** le carry. add r2,r3,r5 additionne r2 et r3 et met le résultat dans r5.
*/

void		cw_ins_add_db(t_proc *proc, t_p *tmp)
{
	ft_printf("P%5d | %s r%d r%d r%d\n", tmp->id, "add",
		proc->mem[(tmp->pc + 2) % MEM_SIZE],
		proc->mem[(tmp->pc + 3) % MEM_SIZE],
		proc->mem[(tmp->pc + 4) % MEM_SIZE]);
}

int			cw_ins_add(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	unsigned int	param[3];

	if (proc->mem[(tmp->pc + 2) % MEM_SIZE] > 0 && proc->mem[(tmp->pc + 2) %
		MEM_SIZE] <= REG_NUMBER && proc->mem[(tmp->pc + 3) % MEM_SIZE] > 0 &&
		proc->mem[(tmp->pc + 3) % MEM_SIZE] <= REG_NUMBER &&
		proc->mem[(tmp->pc + 4) % MEM_SIZE] > 0 && proc->mem[(tmp->pc + 4) %
		MEM_SIZE] <= REG_NUMBER)
	{
		param[0] = cw_get_data_reg(
			tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1);
		param[1] = cw_get_data_reg(
			tmp, proc->mem[(tmp->pc + 3) % MEM_SIZE] - 1);
		param[2] = param[0] + param[1];
		tmp->reg[proc->mem[(tmp->pc + 4) % MEM_SIZE] - 1][0] = param[2] >> 24;
		tmp->reg[proc->mem[(tmp->pc + 4) % MEM_SIZE] - 1][1] = param[2] >> 16;
		tmp->reg[proc->mem[(tmp->pc + 4) % MEM_SIZE] - 1][2] = param[2] >> 8;
		tmp->reg[proc->mem[(tmp->pc + 4) % MEM_SIZE] - 1][3] = param[2];
		tmp->carry = param[2] == 0 ? 1 : 0;
		if (g_bon['d'])
			cw_ins_add_db(proc, tmp);
	}
	return (5);
}
