/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor_cycles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 18:18:16 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 15:14:33 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Affiche la mémoire selon la norme imposée dans le sujet : 32 octets par
** ligne.
*/

void			cw_dump_display(t_proc *proc)
{
	int			i;

	i = 0;
	if (g_bon['z'])
		cw_dump_display_zazlike(proc);
	else
	{
		while (i < MEM_SIZE)
		{
			if (i != 0)
				i % 32 == 0 ? ft_printf("\n") : ft_printf(" ");
			ft_printf("%.2hhx", proc->mem[i]);
			i++;
		}
	}
}

/*
** Vérifie qui est le gagnant et l'affiche.
*/

int				cw_cycles_end(t_proc *proc)
{
	int			i;

	if (proc->last_live_num == 0)
	{
		if (g_bon['v'])
			cw_vizualizer_winner(proc, proc->champions[0]);
		else
			ft_printf("Le joueur %d(%s) a gagné\n", proc->champions[0].num,
			proc->champions[0].header->prog_name);
		return (0);
	}
	i = 0;
	while (proc->champions[i].num != 0)
	{
		if (proc->champions[i].num == proc->last_live_num)
			break ;
		i++;
	}
	if (g_bon['v'])
		cw_vizualizer_winner(proc, proc->champions[i]);
	else
		ft_printf("Le joueur %d(%s) a gagné\n", proc->champions[i].num,
		proc->champions[i].header->prog_name);
	return (0);
}

/*
** Efface un processus de la mémoire, dans le cas où ce dernier est le processus
** original alors on passe son flag is_champ à -1 pour signaler qu'il est mort.
*/

t_p				*cw_kill_process(t_proc *proc, t_p *tmp)
{
	t_p			*to_del;

	to_del = tmp;
	if (g_bon['v'])
		cw_vizualizer_pcprint(proc, tmp, (tmp->id_champion + 10));
	tmp = tmp->next;
	if (to_del != NULL)
	{
		if (to_del->next != NULL)
			to_del->next->prev = to_del->prev;
		if (to_del->prev != NULL)
			to_del->prev->next = to_del->next;
		if (to_del == proc->process)
			proc->process = tmp;
		free(to_del);
		to_del = NULL;
	}
	if (g_bon['s'])
		printf("\a");
	proc->nb_proc--;
	return (tmp);
}

/*
** Vérifie que tous les processus ont fait au moins un live durant la période
** donnée.
*/

void			cw_cycles_checks_lives(t_proc *proc)
{
	t_p			*tmp;

	tmp = proc->process;
	while (tmp != NULL)
	{
		if (tmp->lives == 0)
			tmp = cw_kill_process(proc, tmp);
		else
		{
			tmp->lives = 0;
			tmp = tmp->next;
		}
	}
}

/*
** cw_cycles_checks va vérifier en fin de cycle différentes choses, dont les
** condtions de victoires.
*/

int				cw_cycles_checks(t_proc *proc, int *c_to_die)
{
	if (proc->dump != 0 && proc->c == proc->dump)
	{
		cw_dump_display(proc);
		return (0);
	}
	if (*c_to_die == 0)
	{
		proc->checks++;
		if (proc->lives_total >= NBR_LIVE)
			proc->c_to_die -= CYCLE_DELTA;
		if (proc->checks == MAX_CHECKS)
		{
			proc->c_to_die -= CYCLE_DELTA;
			proc->checks = 0;
		}
		cw_cycles_checks_lives(proc);
		proc->lives_total = 0;
		*c_to_die = proc->c_to_die;
	}
	if (proc->nb_proc == 0 || proc->c_to_die <= 0)
		return (cw_cycles_end(proc));
	return (1);
}
