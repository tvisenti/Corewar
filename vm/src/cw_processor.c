/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 12:15:17 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 12:00:22 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Incrémente le PC de la size renvoyé par la fonction de l'instruction. Cette
** dernière calcule la size du saut de PC à partir de la taille attendue des
** paramètres donnés par l'OCP. S'il n'y en a pas, alors on a une taille
** définie.
** Si le visualiseur est activé, l'ancien PC en couleur est réinitialisé (mis
** en blanc et noir) et le nouveau hérite de la couleur en surbrillance.
*/

void		cw_exec_process_pcincrement(t_proc *proc, t_p *tmp, int size)
{
	if (g_bon['v'])
		cw_vizualizer_pcprint(proc, tmp, (tmp->id_champion + 10));
	tmp->pc = (tmp->pc + (unsigned short)size) % MEM_SIZE;
	cw_get_opcode(proc, tmp);
	if (g_bon['v'])
		cw_vizualizer_pcprint(proc, tmp, tmp->id_champion);
}

/*
** Effectue l'instruction puis fait sauter le PC et réinitialise le cycles
** d'instruction avec la nouvelle valeur.
** Si une instruction n'était pas em cours (tmp->ins == NULL) alors on signale
** cette instruction et on charge le temps de l'instruction.
*/

void		cw_exec_process_instruct(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	int		size;

	cw_ins_ocp(proc, tmp, ocp);
	size = g_op[tmp->opcode - 1].ptr(proc, tmp, ocp);
	cw_exec_process_pcincrement(proc, tmp, size);
}

/*
** cw_exec_process itère sur chaque processus pour savoir s'il y a
** quelque chose à faire ou pas. Si le temps d'une instruction est écoulé, alors
** elle va appeler la fonction qui exécute. Si non, elle incrémente le PC
** jusqu'à tomber sur une instruction.
*/

void		cw_exec_process(t_proc *proc)
{
	t_p			*tmp;
	t_ocp		ocp;

	tmp = proc->process;
	while (tmp)
	{
		if (tmp->opcode > 0x00 && tmp->opcode < 0x11)
		{
			if (tmp->ins_c == 0)
				cw_exec_process_instruct(proc, tmp, &ocp);
			else
				tmp->ins_c--;
		}
		else
			cw_exec_process_pcincrement(proc, tmp, 1);
		tmp = tmp->next;
	}
}

/*
** cw_processor mîme le processeur.
** Elle exécute les cycles, lit la mémoire tout en traitant les instructions.
*/

int			cw_processor(t_proc *proc)
{
	int		c_check;
	int		c_to_die;

	c_check = 1;
	proc->c_to_die = CYCLE_TO_DIE + CYCLE_DELTA;
	proc->c = 1;
	proc->lives_total = 0;
	proc->checks = 0;
	proc->total_id = proc->nb_proc;
	cw_load_ins_c(proc);
	c_to_die = proc->c_to_die;
	while (c_check)
	{
		if (g_bon['c'])
			ft_printf("It is now cycle %d\n", proc->c);
		cw_exec_process(proc);
		c_check = cw_cycles_checks(proc, &c_to_die);
		c_to_die--;
		proc->c++;
	}
	return (1);
}
