/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_get_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:16:01 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 17:42:08 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Récupère le contenu d'un registre et retourne ce dernier dans un int.
*/

unsigned int		cw_get_data_reg(t_p *champ, unsigned char reg)
{
	unsigned int	ret;

	ret = (champ->reg[reg][0] << 24 & 0xff000000) |
	(champ->reg[reg][1] << 16 & 0x00ff0000) |
	(champ->reg[reg][2] << 8 & 0x0000ff00) |
	(champ->reg[reg][3] & 0x000000ff);
	return (ret);
}

unsigned int		cw_get_data_dir(t_proc *proc, t_p *champ,
					unsigned int sze, int dir)
{
	unsigned int	ret;

	if (dir == 2)
		ret = proc->mem[sze % MEM_SIZE] << 8 | proc->mem[(sze + 1) % MEM_SIZE];
	else
		ret = proc->mem[sze % MEM_SIZE] << 24 |
		proc->mem[(sze + 1) % MEM_SIZE] << 16 |
		proc->mem[(sze + 2) % MEM_SIZE] << 8 |
		proc->mem[(sze + 3) % MEM_SIZE];
	return (ret);
}

unsigned int		cw_get_data_ind(t_proc *proc, t_p *champ,
					unsigned int sze)
{
	int				ret;
	short			ind;

	ind = (short)(proc->mem[sze % MEM_SIZE] << 8 |
		proc->mem[(sze + 1) % MEM_SIZE])
	% IDX_MOD;
	ret = (proc->mem[(champ->pc + ind) % MEM_SIZE] << 24
		| proc->mem[(champ->pc + ind + 1) % MEM_SIZE] << 16
		| proc->mem[(champ->pc + ind + 2) % MEM_SIZE] << 8
		| proc->mem[(champ->pc + ind + 3) % MEM_SIZE]);
	return (ret);
}

unsigned int		cw_get_data_ind_l(t_proc *proc, t_p *champ,
					unsigned int sze)
{
	short			ret;
	short			ind;

	ind = (short)(proc->mem[sze % MEM_SIZE] << 8 |
		proc->mem[(sze + 1) % MEM_SIZE]);
	ret = (proc->mem[(champ->pc + ind) % MEM_SIZE] << 24
		| proc->mem[(champ->pc + ind + 1) % MEM_SIZE] << 16
		| proc->mem[(champ->pc + ind + 2) % MEM_SIZE] << 8
		| proc->mem[(champ->pc + ind + 3) % MEM_SIZE]);
	return (ret);
}
