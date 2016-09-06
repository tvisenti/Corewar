/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 18:11:18 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** sti r2,%4,%5 sti copie REG_SIZE octet de r2 a l’adresse (4 + 5)
** Les paramètres 2 et 3 sont des index. Si les paramètres 2 ou 3
** sont des registres, on utilisera leur contenu comme un index.
*/

void		cw_ins_sti_db(t_proc *proc, t_p *tmp, t_ocp *ocp, int p[3])
{
	ft_printf("P%5d | %s ", tmp->id, "sti");
	ft_printf("r%d ", p[0]);
	ft_printf("%d ", p[1]);
	ft_printf("%d\n", p[2]);
	ft_printf("%6s | -> store to %d + %d = %d (with pc and mod %d)\n",
		" ", p[1], p[2], p[1] + p[2], (tmp->pc + (p[1] + p[2]) % IDX_MOD));
}

void		cw_exec_sti(t_proc *proc, t_p *tmp, int p[3])
{
	unsigned int	i;
	int				total;

	i = -1;
	total = (p[1] + p[2]) % IDX_MOD;
	while (++i < REG_SIZE)
	{
		proc->mem[(tmp->pc + total + i) % MEM_SIZE] =
		tmp->reg[p[0] - 1][i];
		if (g_bon['v'])
			cw_vizualizer_print(proc, tmp,
				(tmp->pc + total + i) % MEM_SIZE, tmp->reg[p[0] - 1][i]);
	}
}

int			cw_ins_sti_check(t_ocp *ocp, int *p)
{
	if (p[0] < 1 || p[0] > REG_NUMBER || ocp->third == IND_CODE)
		return (1);
	if (p[1] == REG_CODE)
	{
		if (p[1] < 1 || p[1] > REG_NUMBER)
			return (1);
	}
	if (p[2] == REG_CODE)
	{
		if (p[2] < 1 || p[2] > REG_NUMBER)
			return (1);
	}
	return (0);
}

void		cw_ins_sti_init(unsigned char initpzero, t_ocp *ocp,
			unsigned int *p_sze, int *p)
{
	p_sze[0] = cw_ins_param_sze(ocp->first, 2);
	p_sze[1] = cw_ins_param_sze(ocp->second, 2);
	p_sze[2] = cw_ins_param_sze(ocp->third, 2);
	p[0] = initpzero;
	p[1] = 0;
	p[2] = 0;
}

int			cw_ins_sti(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	unsigned int	p_sze[3];
	int				p[3];

	cw_ins_sti_init(proc->mem[tmp->pc + 2], ocp, p_sze, p);
	if (ocp->second == REG_CODE && (proc->mem[tmp->pc + 2 + p_sze[0]] - 1) >= 0
		&& (proc->mem[tmp->pc + 2 + p_sze[0]] - 1) < REG_NUMBER)
		p[1] = cw_get_data_reg(tmp, proc->mem[tmp->pc + 2 + p_sze[0]] - 1);
	else if (ocp->second == DIR_CODE)
		p[1] = (short)cw_get_data_dir(proc, tmp, tmp->pc + 2 + p_sze[0], 2);
	else if (ocp->second == IND_CODE)
		p[1] = cw_get_data_ind(proc, tmp, tmp->pc + 2 + p_sze[0]);
	if (ocp->third == REG_CODE &&
		(proc->mem[tmp->pc + 2 + p_sze[0] + p_sze[1]] - 1) >= 0 &&
		(proc->mem[tmp->pc + 2 + p_sze[0] + p_sze[1]] - 1) < REG_NUMBER)
		p[2] = cw_get_data_reg(
		tmp, proc->mem[tmp->pc + 2 + p_sze[0] + p_sze[1]] - 1);
	else if (ocp->third == DIR_CODE)
		p[2] = (short)cw_get_data_dir(
		proc, tmp, tmp->pc + 2 + p_sze[0] + p_sze[1], 2);
	if (cw_ins_sti_check(ocp, p))
		return (1 + 1 + p_sze[0] + p_sze[1] + p_sze[2]);
	cw_exec_sti(proc, tmp, p);
	if (g_bon['d'] == 1)
		cw_ins_sti_db(proc, tmp, ocp, p);
	return (1 + 1 + p_sze[0] + p_sze[1] + p_sze[2]);
}
