/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 10:34:15 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 11:59:40 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void			cw_proc_init(t_proc *proc)
{
	ft_bzero(proc->mem, sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(proc->champions, sizeof(t_champion) * (MAX_PLAYERS + 1));
	ft_bzero(proc->lives_champions, sizeof(unsigned int) * (MAX_PLAYERS + 1));
	proc->process = NULL;
	proc->dump = 0;
	proc->nb_proc = 0;
	proc->c_to_die = 0;
	proc->c = 0;
	proc->lives_total = 0;
	proc->checks = 0;
	proc->last_live_num = 0;
	proc->total_id = 0;
}

int				main(int ac, char **av)
{
	t_proc		proc;

	cw_proc_init(&proc);
	if (cw_param(av, ac, &proc) <= 0)
		return (ft_printf("Fail !\n"));
	cw_load_ins_mem(&proc);
	if (g_bon['v'])
		cw_vizualizer_processor(&proc);
	else
		cw_processor(&proc);
	return (0);
}
