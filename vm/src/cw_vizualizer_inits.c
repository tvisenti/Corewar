/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer_inits.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/10 11:44:29 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 18:01:12 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Initialisations du visualiseur.
*/

/*
** Affiche le PC de départ en couleur.
*/

void		cw_vizualizer_init_pc(t_proc *proc)
{
	t_p		*tmp;

	tmp = proc->process;
	while (tmp)
	{
		cw_vizualizer_pcprint(proc, tmp, tmp->id_champion);
		tmp = tmp->next;
	}
}

/*
** Récupère l'intervalle où se trouve le champion pour afficher la mémoire avec
** la couleur appropriée.
*/

int			cw_vizualizer_colinit(t_proc *proc, int i)
{
	t_p		*tmp;

	tmp = proc->process;
	while (tmp)
	{
		if (i >= tmp->pc && i <
			(tmp->pc + proc->champions[tmp->id_champion - 1].header->prog_size))
			return ((tmp->id_champion + 10));
		tmp = tmp->next;
	}
	return (5);
}

/*
** Imprime la mémoire octet par octet avec des coordonnées précises selon les
** octets.
*/

void		cw_vizualizer_init_memprint(t_proc *proc)
{
	int			i;
	int			x;
	int			y;

	i = 0;
	x = 1;
	y = 1;
	while (y < 65)
	{
		while (x <= 191)
		{
			wattron(proc->win[0], COLOR_PAIR(cw_vizualizer_colinit(proc, i)));
			mvwprintw(proc->win[0], y, x, "%.2hhx", proc->mem[i]);
			wattroff(proc->win[0], COLOR_PAIR(cw_vizualizer_colinit(proc, i)));
			x += 3;
			i++;
		}
		y++;
		x = 1;
	}
	cw_vizualizer_init_pc(proc);
}

/*
** Initialise les couleurs pour chaque champions, selon leur id. Le 5 est une
** rénitialisation (blanc sur noir).
*/

void		cw_vizualizer_init_colors(void)
{
	init_color(COLOR_WHITE, 400, 400, 400);
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_BLACK, COLOR_CYAN);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(11, COLOR_GREEN, COLOR_BLACK);
	init_pair(12, COLOR_BLUE, COLOR_BLACK);
	init_pair(13, COLOR_RED, COLOR_BLACK);
	init_pair(14, COLOR_CYAN, COLOR_BLACK);
}

/*
** Initialise le visualiseur.
*/

void		cw_vizualizer_init(t_proc *proc)
{
	initscr();
	proc->win[0] = newwin(66, 194, 0, 0);
	proc->win[1] = newwin(66, 70, 0, 194);
	start_color();
	noecho();
	cbreak();
	nodelay(proc->win[0], TRUE);
	nodelay(proc->win[1], TRUE);
	box(proc->win[0], ACS_VLINE, ACS_HLINE);
	refresh();
	cw_vizualizer_init_colors();
}
