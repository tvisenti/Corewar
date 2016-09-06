/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:15:25 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 12:32:01 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette opération modifie le carry. ldi 3,%4,r1 lit IND_SIZE octets a
** l’adresse : (PC + (3 % IDX_MOD)) ajoute 4 à cette valeur. On nommera S
** cette somme. On lit REG_SIZE octet à l’adresse (PC + (S % IDX_MOD))
** que l’on copie dans r1. Les paramètres 1 et 2 sont des index.
** T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG
*/

int			cw_ins_ldi_secondparamhandler(t_proc *proc, t_p *tmp,
										char ocp, unsigned int p_sze)
{
	if (ocp == REG_CODE && proc->mem[(tmp->pc + 2 + p_sze) % MEM_SIZE] > 0
		&& proc->mem[(tmp->pc + 2 + p_sze) % MEM_SIZE] <= REG_NUMBER)
	{
		return (cw_get_data_reg(tmp,
				proc->mem[(tmp->pc + 2 + p_sze) % MEM_SIZE] - 1));
	}
	else if (ocp == DIR_CODE)
	{
		return ((short)cw_get_data_dir(proc, tmp,
				(tmp->pc + 2 + p_sze) % MEM_SIZE, 2));
	}
	return (0);
}

int			cw_ins_ldi_firstparamhandler(t_proc *proc, t_p *tmp,
										char ocp)
{
	if (ocp == REG_CODE && proc->mem[(tmp->pc + 2) % MEM_SIZE] > 0
		&& proc->mem[(tmp->pc + 2) % MEM_SIZE] <= REG_NUMBER)
		return (cw_get_data_reg(tmp,
				proc->mem[(tmp->pc + 2) % MEM_SIZE] - 1));
	else if (ocp == DIR_CODE)
		return ((short)cw_get_data_dir(proc, tmp,
				((tmp->pc + 2) % MEM_SIZE), 2));
	else if (ocp == IND_CODE)
		return (cw_get_data_ind(proc, tmp, (tmp->pc + 2) % MEM_SIZE));
	return (0);
}

void		cw_ins_ldi_b(int p[3], t_p *tmp, t_ocp *ocp)
{
	if (g_bon['d'])
	{
		ft_printf("P%5d | %s ", tmp->id, "ldi");
		ft_printf("%d ", p[0]);
		ft_printf("%d ", p[1]);
		if (ocp->third == REG_CODE)
			ft_printf("r%d\n", p[2]);
		else
			ft_printf("%d\n", p[2]);
		ft_printf("%8 | -> load from %d + %d = %d (with pc and mod %d)\n",
			p[0], p[1], p[0] + p[1], tmp->pc + (p[0] + p[1]) % IDX_MOD);
	}
}

int			cw_ins_ldi(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	int				p[3];
	unsigned int	p_sze[3];
	int				ret;

	p_sze[0] = cw_ins_param_sze(ocp->first, 2);
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	p_sze[2] = cw_ins_param_sze(ocp->third, 2);
	if (ocp->third != REG_CODE)
		return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
	p[0] = cw_ins_ldi_firstparamhandler(proc, tmp, ocp->first);
	p[1] = cw_ins_ldi_secondparamhandler(proc,
		tmp, ocp->second, p_sze[0]);
	p[2] = proc->mem[(tmp->pc + 2 + p_sze[0] + p_sze[1]) % MEM_SIZE];
	ret = cw_get_data_dir(proc, tmp, (tmp->pc + ((p[0] + p[1]) % IDX_MOD)), 4);
	if (p[2] > 0 && p[2] <= REG_NUMBER)
	{
		tmp->reg[p[2] - 1][0] = ret >> 24;
		tmp->reg[p[2] - 1][1] = ret >> 16;
		tmp->reg[p[2] - 1][2] = ret >> 8;
		tmp->reg[p[2] - 1][3] = ret;
	}
	tmp->carry = ret == 0 ? 1 : 0;
	cw_ins_ldi_b(p, tmp, ocp);
	return (2 + p_sze[0] + p_sze[1] + p_sze[2]);
}
