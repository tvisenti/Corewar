/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer_proc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 14:29:42 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 11:11:28 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Initialise les variables du visualiseur.
*/

void		cw_vizualizer_proc_init(t_proc *proc, int *c_to_die)
{
	proc->c_to_die = CYCLE_TO_DIE + CYCLE_DELTA;
	proc->c = 1;
	proc->lives_total = 0;
	proc->checks = 0;
	cw_load_ins_c(proc);
	*c_to_die = proc->c_to_die;
	cw_vizualizer_init(proc);
	cw_vizualizer_init_memprint(proc);
	keypad(stdscr, TRUE);
}

/*
** Permet de contrôler le jump de cycles avec les touches.
*/

int			cw_vizualizer_proc_control(t_proc *proc, int i)
{
	int	ch;

	wrefresh(proc->win[1]);
	wrefresh(proc->win[0]);
	refresh();
	ch = getch();
	if (ch == 32)
		return (10);
	else if (ch == 127)
		return (100);
	else
		return (1);
}

/*
** Le processeur du Corewar équipé du visualiseur.
*/

int			cw_vizualizer_processor(t_proc *proc)
{
	int		c_check;
	int		i;
	int		c_to_die;

	c_check = 1;
	i = 0;
	cw_vizualizer_proc_init(proc, &c_to_die);
	while (c_check)
	{
		cw_exec_process(proc);
		cw_vizualizer_infos(proc);
		if (i == 0)
			i = cw_vizualizer_proc_control(proc, i);
		i--;
		c_check = cw_cycles_checks(proc, &c_to_die);
		c_to_die--;
		proc->c++;
	}
	delwin(proc->win[1]);
	delwin(proc->win[0]);
	endwin();
	return (1);
}
