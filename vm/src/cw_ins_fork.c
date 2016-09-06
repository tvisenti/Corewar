/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:29 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 15:10:08 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction n’est pas suivie d’octet pour décrire les paramètres.
** Elle prend toujours un index et crée un nouveau programme qui s’exécute
** à partir de l’adresse : (PC + (premier paramètre % IDX_MOD)).
** Fork %34 crée un nouveau programme. Le nouveau programme
** hérite des différents états du père.
*/

void		cw_ins_fork_db(t_proc *proc, t_p *tmp, t_ocp *ocp,
			short int p)
{
	ft_printf("P%5d | %s %d (%d)\n", tmp->id,
		"fork", p, (tmp->pc + (p % IDX_MOD)) % MEM_SIZE);
}

void		cw_ins_fork_duplicate_reg(t_p *new, t_p *old)
{
	int		i;
	int		j;

	i = 0;
	while (i < REG_NUMBER)
	{
		j = 0;
		while (j < REG_SIZE)
		{
			new->reg[i][j] = old->reg[i][j];
			j++;
		}
		i++;
	}
}

int			cw_ins_fork(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	short int	p;
	t_p			*new;

	p = (short int)cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 2);
	new = cw_lst_new(proc->champions[tmp->id_champion - 1].id_champion);
	proc->process = cw_lst_push(proc, new);
	cw_ins_fork_duplicate_reg(new, tmp);
	new->pc = (tmp->pc + (unsigned short)(p % IDX_MOD)) % MEM_SIZE;
	new->carry = tmp->carry;
	cw_get_opcode(proc, new);
	new->lives = 0;
	new->id = ++proc->total_id;
	proc->nb_proc++;
	if (g_bon['d'] == 1)
		cw_ins_fork_db(proc, tmp, ocp, p);
	return (3);
}
