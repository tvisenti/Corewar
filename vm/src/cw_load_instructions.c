/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_load_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 18:12:18 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int				cw_biggest_num(t_proc *proc)
{
	int			i;
	int			num;
	int			ret;

	i = 0;
	ret = 0;
	num = 0;
	while (proc->champions[i].num)
	{
		if (num < proc->champions[i].num && proc->champions[i].insert)
		{
			num = proc->champions[i].num;
			ret = i;
		}
		i++;
	}
	return (ret);
}

int				cw_load_ins_mem(t_proc *proc)
{
	int			cnt;
	int			i;
	int			cnt2;
	t_p			*last;

	cnt = 0;
	cnt2 = -1;
	while (++cnt2 < proc->nb_proc)
	{
		i = cw_biggest_num(proc);
		cw_lst_add(&proc->process, cw_lst_new(proc->champions[i].id_champion));
		last = cw_lst_last(proc->process);
		last->reg[0][0] = proc->champions[i].num >> 24;
		last->reg[0][1] = proc->champions[i].num >> 16;
		last->reg[0][2] = proc->champions[i].num >> 8;
		last->reg[0][3] = proc->champions[i].num;
		last->id = last->prev ? last->prev->id + 1 : 1;
		ft_memcpy(&(proc->mem[cnt * MEM_SIZE / proc->nb_proc]),
		proc->champions[i].insert, proc->champions[i].header->prog_size);
		last->pc = cnt * MEM_SIZE / proc->nb_proc;
		free(proc->champions[i].insert);
		proc->champions[i].insert = NULL;
		cnt++;
	}
	return (1);
}
