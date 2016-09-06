/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_lld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 16:07:31 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 12:27:27 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Comme ld sans le %IDX_MOD Cette opération modifie le carry.
*/

int			cw_ins_lld(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[2];
	unsigned int	p[2];

	p_sze[0] = cw_ins_param_sze(ocp->first, 4);
	p_sze[1] = cw_ins_param_sze(ocp->second, 4);
	if (ocp->first == DIR_CODE)
		p[0] = cw_get_data_dir(proc, tmp, (tmp->pc + 2) % MEM_SIZE, 4);
	else if (ocp->first == IND_CODE)
		p[0] = cw_get_data_ind_l(proc, tmp, (tmp->pc + 2) % MEM_SIZE);
	p[1] = proc->mem[(tmp->pc + 2 + p_sze[0]) % MEM_SIZE];
	if (ocp->first == REG_CODE || p[1] < 1 || p[1] > REG_NUMBER ||
		ocp->second != REG_CODE || ocp->first == 0)
		return (2 + p_sze[0] + p_sze[1]);
	tmp->reg[p[1] - 1][0] = p[0] >> 24;
	tmp->reg[p[1] - 1][1] = p[0] >> 16;
	tmp->reg[p[1] - 1][2] = p[0] >> 8;
	tmp->reg[p[1] - 1][3] = p[0];
	tmp->carry = p[0] == 0 ? 1 : 0;
	if (g_bon['d'] == 1)
		cw_bonus_db_twoparams(proc, tmp, ocp, (int*)p);
	return (2 + p_sze[0] + p_sze[1]);
}
