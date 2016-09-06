/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 17:28:55 by tvisenti          #+#    #+#             */
/*   Updated: 2016/08/01 10:32:38 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Check la suite de la validité des args de chaque instruct
*/

int		asm_check_arg_sec(char **line, int op)
{
	if (op == 3 && asm_check_reg(line, 1) && (asm_check_ind(line, 0) ||
	asm_check_reg(line, 0)))
		return (1);
	if ((op == 4 || op == 5) && asm_check_reg(line, 1) &&
	asm_check_reg(line, 1) && asm_check_reg(line, 0))
		return (1);
	if ((op == 10 || op == 14) && (asm_check_dir(line, op, 1) ||
	asm_check_reg(line, 1) || asm_check_ind(line, 1)) &&
	(asm_check_dir(line, op, 1) || asm_check_reg(line, 1)) &&
	asm_check_reg(line, 0))
		return (1);
	return (asm_error(8));
}

/*
** Check la validité des args de chaque instruct
*/

int		asm_check_arg(char **line, int op)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if ((op == 1 || op == 9 || op == 12 || op == 15) &&
	asm_check_dir(line, op, 0))
		return (1);
	if ((op == 2 || op == 13) && (asm_check_dir(line, op, 1) ||
	asm_check_ind(line, 1)) && asm_check_reg(line, 0))
		return (1);
	if ((op == 6 || op == 7 || op == 8) && ((asm_check_dir(line, op, 1) ||
	asm_check_reg(line, 1) || asm_check_ind(line, 1))
	&& (asm_check_dir(line, op, 1) || asm_check_reg(line, 1) ||
	asm_check_ind(line, 1)) && asm_check_reg(line, 0)))
		return (1);
	if (op == 11 && asm_check_reg(line, 1) && (asm_check_dir(line, op, 1) ||
	asm_check_reg(line, 1) || asm_check_ind(line, 1)) &&
	(asm_check_dir(line, op, 0) || asm_check_reg(line, 0)))
		return (1);
	if (op == 16 && asm_check_reg(line, 0))
		return (1);
	return (asm_check_arg_sec(line, op));
}
