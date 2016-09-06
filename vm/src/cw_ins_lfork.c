/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_lfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 16:07:20 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 15:10:18 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Comme fork sans le %IDX_MOD Cette opération modifie le carry.
*/

void		cw_ins_lfork_db(t_proc *proc, t_p *tmp, t_ocp *ocp,
			short int p)
{
	ft_printf("P%5d | %s %d (%d)\n", tmp->id,
		"lfork", p, (tmp->pc + p) % MEM_SIZE);
}

int			cw_ins_lfork(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	short int	p;
	t_p			*new;

	p = (short int)cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 2);
	new = cw_lst_new(proc->champions[tmp->id_champion - 1].id_champion);
	proc->process = cw_lst_push(proc, new);
	cw_ins_fork_duplicate_reg(new, tmp);
	new->pc = (tmp->pc + (unsigned short)p) % MEM_SIZE;
	new->carry = tmp->carry;
	cw_get_opcode(proc, new);
	new->lives = 0;
	new->id = ++proc->total_id;
	proc->nb_proc++;
	if (g_bon['d'] == 1)
		cw_ins_lfork_db(proc, tmp, ocp, p);
	return (3);
}
