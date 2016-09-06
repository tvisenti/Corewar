/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 12:57:24 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 12:10:43 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Même que and mais avec le ou exclusif (^ du c).
*/

void		cw_exec_xor(t_p *tmp, unsigned int p[3],
			unsigned int p_sze[3], t_ocp *ocp)
{
	unsigned int	total;

	total = p[1] ^ p[0];
	if (p[2] > 0 && p[2] <= REG_NUMBER && p_sze[0] && p_sze[1] && p_sze[2])
	{
		tmp->reg[p[2] - 1][0] = total >> 24;
		tmp->reg[p[2] - 1][1] = total >> 16;
		tmp->reg[p[2] - 1][2] = total >> 8;
		tmp->reg[p[2] - 1][3] = total;
		if (total == 0)
			tmp->carry = 1;
		else
			tmp->carry = 0;
		if (g_bon['d'])
		{
			ft_printf("P%5d | %s ", tmp->id, "xor");
			ft_printf("%d ", p[0]);
			ft_printf("%d ", p[1]);
			if (ocp->third == REG_CODE)
				ft_printf("r%d\n", p[2]);
			else
				ft_printf("%d\n", p[2]);
		}
	}
}

int			cw_ins_xor(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	unsigned int	p[3];

	p_sze[0] = cw_ins_param_sze(ocp->first, 4);
	p_sze[1] = cw_ins_param_sze(ocp->second, 4);
	p_sze[2] = cw_ins_param_sze(ocp->third, 4);
	if (ocp->first == REG_CODE && proc->mem[(tmp->pc + 2) % MEM_SIZE] > 0 &&
		proc->mem[(tmp->pc + 2) % MEM_SIZE] <= REG_NUMBER)
		p[0] = cw_get_data_reg(tmp, proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1);
	else if (ocp->first == DIR_CODE)
		p[0] = cw_get_data_dir(proc, tmp, tmp->pc + 2, 4);
	else if (ocp->first == IND_CODE)
		p[0] = cw_get_data_ind(proc, tmp, tmp->pc + 2);
	if (ocp->second == REG_CODE &&
		proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] > 0 &&
		proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] <= REG_NUMBER)
		p[1] = cw_get_data_reg(tmp,
			proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE] - 1);
	else if (ocp->second == DIR_CODE)
		p[1] = cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 4);
	else if (ocp->second == IND_CODE)
		p[1] = cw_get_data_ind(proc, tmp, tmp->pc + 2 + p_sze[0]);
	p[2] = proc->mem[(tmp->pc + 2 + p_sze[0] + p_sze[1]) % MEM_SIZE];
	cw_exec_xor(tmp, p, p_sze, ocp);
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
