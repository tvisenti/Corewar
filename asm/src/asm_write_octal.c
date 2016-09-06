/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_octal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <gseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 17:47:55 by gseropia          #+#    #+#             */
/*   Updated: 2016/08/01 15:31:28 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void	asm_opcode_assign(int *octout, int i, int check, char *file)
{
	if (check == 1 && file[i] == 'r')
		*octout = 0x40;
	else if (check == 1 && file[i] == '%')
		*octout = 0x80;
	else if (check == 1)
		*octout = 0xC0;
	if (check == 2 && file[i] == 'r')
		*octout = 0x10;
	else if (check == 2 && file[i] == '%')
		*octout = 0x20;
	else if (check == 2)
		*octout = 0x30;
	if (check == 3 && file[i] == 'r')
		*octout = 0x4;
	else if (check == 3 && file[i] == '%')
		*octout = 0x8;
	else if (check == 3)
		*octout = 0xC;
}

int		asm_opcode(int fd, int arg, int i, char *file)
{
	int	octout;
	int	octin;

	octin = 0;
	octout = 0;
	asm_opcode_assign(&octout, i, 1, file);
	octin = (octin | octout);
	if (arg > 1)
	{
		i = asm_move_my_i(i, file);
		asm_opcode_assign(&octout, i, 2, file);
		octin = (octin | octout);
	}
	if (arg > 2)
	{
		i = asm_move_my_i(i, file);
		asm_opcode_assign(&octout, i, 3, file);
		octin = (octin | octout);
	}
	g_temp++;
	write(fd, &octin, 1);
	return (1);
}

int		asm_write_dir(int fd, int size, t_label *label, char **file)
{
	int	i;
	int	len;

	len = 0;
	if (!(i = 0) && **file != DIRECT_CHAR)
		return (0);
	if (++(*file) && **file == LABEL_CHAR && (*file)++)
		i = asm_calculate_i(*file, label);
	else
		i = ft_atoi(*file);
	if (size == 4)
		i = cw_invert_endian(i);
	else
		i = cw_invert_endian2(i);
	write(fd, &i, size);
	g_temp = g_temp + size;
	asm_move_separator(file);
	return (1);
}

int		asm_write_ind(int fd, t_label *label, char **file)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	if (**file == LABEL_CHAR && (*file)++)
		i = asm_calculate_i(*file, label);
	else
		i = ft_atoi(*file);
	i = cw_invert_endian2(i);
	write(fd, &i, T_IND);
	g_temp = g_temp + T_IND;
	asm_move_separator(file);
	return (1);
}

int		asm_write_reg(int fd, char **file)
{
	int	i;

	i = 0;
	if (**file != 'r')
		return (0);
	i = ft_atoi(++(*file));
	write(fd, &i, T_REG);
	g_temp = g_temp + T_REG;
	asm_move_separator(file);
	return (1);
}
