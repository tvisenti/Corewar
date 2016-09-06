/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vizualizer_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 11:24:21 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Permet d'imprimer un octet dans la représentation de la mémoire du
** visualiseur.
*/

void		cw_vizualizer_print(t_proc *proc, t_p *tmp, int where,
			unsigned char what)
{
	int		*coord;

	coord = (int*)malloc(sizeof(int) * 2);
	coord[0] = where / 64 + 1;
	if (where % 64 == 0)
		coord[1] = where % 64 + 1;
	else
		coord[1] = where % 64 * 3 + 1;
	wattron(proc->win[0], COLOR_PAIR(tmp->id_champion + 10));
	mvwprintw(proc->win[0], coord[0], coord[1], "%.2hhx", what);
	wattroff(proc->win[0], COLOR_PAIR(tmp->id_champion + 10));
	free(coord);
}

/*
** Permet de mettre en couleur le PC en cours. Prend un paramètre col, pour
** couleur, qui permet de sélectionner quel COLOR_PAIR choisir. Ce qui permet
** une plus grande souplesse pour "allumer" ou "éteindre" un PC. Le COLOR_PAIR
** 5 permet de réinitialiser la couleur.
*/

void		cw_vizualizer_pcprint(t_proc *proc, t_p *tmp, char col)
{
	int		*coord;

	coord = (int*)malloc(sizeof(int) * 2);
	coord[0] = tmp->pc / 64 + 1;
	if (tmp->pc % 64 == 0)
		coord[1] = tmp->pc % 64 + 1;
	else
		coord[1] = tmp->pc % 64 * 3 + 1;
	wattron(proc->win[0], COLOR_PAIR(col));
	mvwprintw(proc->win[0], coord[0], coord[1], "%.2hhx", proc->mem[tmp->pc]);
	wattroff(proc->win[0], COLOR_PAIR(col));
	free(coord);
}

/*
** Affiche les informations se trouvant sur le côté de la VM. No bullshit.
*/

void		cw_vizualizer_infos_side(t_proc *proc, int y)
{
	mvwprintw(proc->win[1], (y = y + 1), 2, "lives period\t: %8d",
		proc->lives_total);
	mvwprintw(proc->win[1], (y = y + 1), 2, "nb process\t: %8d",
		proc->nb_proc);
	mvwprintw(proc->win[1], (y = y + 1), 2, "CYCLE_TO_DIE\t: %8d",
		proc->c_to_die - CYCLE_DELTA);
	mvwprintw(proc->win[1], (y = y + 1), 2, "CYCLE_DELTA\t: %8d", CYCLE_DELTA);
	mvwprintw(proc->win[1], (y = y + 1), 2, "NBR_LIVE\t: %8d", NBR_LIVE);
	mvwprintw(proc->win[1], (y = y + 1), 2, "MAX_CHECKS\t: %8d", MAX_CHECKS);
}

/*
** Affiche les informations concernant les joueurs.
*/

void		cw_vizualizer_infos(t_proc *proc)
{
	int			i;
	int			y;

	mvwprintw(proc->win[1], 1, 2, "Cycle\t: %8d", proc->c);
	y = 4;
	i = 0;
	while (proc->champions[i].num)
	{
		wattron(proc->win[1],
			COLOR_PAIR(proc->champions[i].id_champion + 10) | A_BOLD);
		mvwprintw(proc->win[1], y, 2, "Player %d : %s", proc->champions[i].num,
			proc->champions[i].header->prog_name);
		wattroff(proc->win[1],
			COLOR_PAIR(proc->champions[i].id_champion + 10) | A_BOLD);
		mvwprintw(proc->win[1], (y = y + 1), 4, "lives : %u",
			proc->lives_champions[proc->champions[i].id_champion - 1]);
		y += 2;
		i++;
	}
	cw_vizualizer_infos_side(proc, y);
}

/*
** Fonction qui affiche le gagnant dans le visualiseur.
*/

void		cw_vizualizer_winner(t_proc *proc, t_champion winner)
{
	werase(proc->win[1]);
	wattron(proc->win[1], COLOR_PAIR(winner.id_champion + 10) | A_BOLD);
	mvwprintw(proc->win[1], 60, 2, "Le joueur %d(%s) a gagné", winner.num,
	winner.header->prog_name);
	wattroff(proc->win[1], COLOR_PAIR(winner.id_champion + 10) | A_BOLD);
	mvwprintw(proc->win[1], 62, 2, "(appuyer sur [echap] pour quitter)");
	wrefresh(proc->win[1]);
	while (1)
	{
		if (getch() == 27)
			return ;
	}
}
