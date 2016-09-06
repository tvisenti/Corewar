/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_ins_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 15:17:16 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 12:34:26 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

/*
** Cette instruction est suivie d’un octet de paramétrage pour décrire
** les paramètres. Elle prend en paramètre un registre et a che le
** caractère dont le code ascii est présent dans ce registre (base
** 10). (un modulo 256 est appliqué au code ascii, le caractère
** est affiché sur la sortie standard).
*/

int			cw_ins_aff(t_proc *proc, t_p *tmp, t_ocp *ocp)
{
	unsigned int	p;
	int				reg;

	reg = proc->mem[(tmp->pc + 2) % MEM_SIZE];
	if (reg >= 1 && reg <= REG_SIZE && g_bon['m'] == 0)
	{
		p = cw_get_data_reg(tmp, reg - 1) % 256;
		ft_printf("%c", p);
	}
	return (3);
}
