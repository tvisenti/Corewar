/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_manage_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/05 18:02:12 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

t_p				*cw_lst_new(int id_champ)
{
	t_p			*new;
	int			reg_sze;
	int			reg_nb;

	if ((new = malloc(sizeof(t_p))) == NULL)
		return (NULL);
	reg_sze = -1;
	reg_nb = -1;
	new->next = NULL;
	new->prev = NULL;
	while (++reg_nb < REG_NUMBER)
	{
		while (++reg_sze < REG_SIZE)
			new->reg[reg_nb][reg_sze] = 0;
		reg_sze = -1;
	}
	new->ins_c = 0;
	new->lives = 0;
	new->id = 0;
	new->id_champion = id_champ;
	new->pc = 0;
	new->opcode = 0;
	new->carry = 0;
	return (new);
}

t_p				*cw_lst_push(t_proc *proc, t_p *new)
{
	if (new == NULL)
	{
		ft_printf("In - cw_lst_push - new is NULL\n");
		return (proc->process);
	}
	if (proc->process != NULL)
	{
		proc->process->prev = new;
		new->next = proc->process;
		new->prev = NULL;
	}
	proc->process = new;
	return (proc->process);
}

void			cw_lst_add(t_p **begin, t_p *new)
{
	t_p			*tmp;

	if (new == NULL)
	{
		ft_printf("In - cw_lst_add - new is NULL\n");
		return ;
	}
	tmp = *begin;
	if (*begin)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
	{
		*begin = new;
		new->prev = NULL;
	}
	new->next = NULL;
}

int				cw_lst_sze(t_p *begin)
{
	t_p		*tmp;
	int		sze;

	sze = 0;
	tmp = begin;
	while (tmp)
	{
		tmp = tmp->next;
		sze++;
	}
	return (sze);
}
