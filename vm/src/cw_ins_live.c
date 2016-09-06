/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:05:56 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 15:23:20 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Suivie de 4 octets qui représente le numéro du joueur. Cette instruction
** indique que ce joueur est en vie. Pas d’octet de codage des paramètres.
*/

static void	cw_ins_live_display(t_proc *proc, t_p *tmp, t_champion *champ)
{
	if (g_bon['v'])
	{
		werase(proc->win[1]);
		mvwprintw(proc->win[1], 60, 2,
			"Un processus dit que le joueur %d(%s) est en vie\n",
			champ->num, champ->header->prog_name);
	}
	else if (g_bon['d'])
		ft_printf("P%5d | %s %d\n", tmp->id, "live", champ->num);
	else if (proc->dump == 0 && g_bon['m'] == 0)
		ft_printf("Un processus dit que le joueur %d(%s) est en vie\n",
			champ->num, champ->header->prog_name);
}

int			cw_ins_live(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	int				i;
	unsigned int	check;

	i = 0;
	check = cw_get_data_dir(proc, tmp, (tmp->pc + 1) % MEM_SIZE, 4);
	tmp->lives++;
	proc->lives_total++;
	while (proc->champions[i].num != 0)
	{
		if (proc->champions[i].num == check)
		{
			proc->lives_champions[tmp->id_champion - 1] += 1;
			cw_ins_live_display(proc, tmp, &proc->champions[i]);
			proc->last_live_num = proc->champions[i].num;
			return (5);
		}
		i++;
	}
	if (g_bon['d'])
		ft_printf("P%5d | %s %d\n", tmp->id, "live", check);
	return (5);
}
