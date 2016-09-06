/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_instruction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gseropia <gseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 14:57:05 by gseropia          #+#    #+#             */
/*   Updated: 2016/08/29 15:04:19 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Check si le SEPARATOR_CHAR est correct
*/

int		asm_check_virgule(char **line)
{
	while (**line == '\t' || **line == ' ')
		(*line)++;
	if (**line != SEPARATOR_CHAR)
		return (asm_error(8));
	(*line)++;
	while (**line == '\t' || **line == ' ')
		(*line)++;
	return (1);
}

/*
** Check si le direct est correct
*/

int		asm_check_dir(char **line, int op, int check)
{
	if (**line == DIRECT_CHAR)
	{
		if (op > 8 && op != 13)
			g_pos = g_pos + 2;
		else
			g_pos = g_pos + 4;
		(*line)++;
		if (**line != LABEL_CHAR && !(**line >= '0' && **line <= '9') &&
		**line != '-' && **line != '+')
			asm_error_sec(15);
		if (**line == LABEL_CHAR)
			(*line)++;
		else if (**line == '+' || **line == '-')
			(*line)++;
		while (**line && ft_strchr(LABEL_CHARS, **line))
			(*line)++;
		while (**line == ' ' || **line == '\t')
			(*line)++;
		if (check == 1)
			return (asm_check_virgule(line));
		return (1);
	}
	return (0);
}

/*
** Check si le registre est correct
*/

int		asm_check_reg(char **line, int check)
{
	int reg;

	reg = 0;
	if (**line == 'r')
	{
		(*line)++;
		reg = ft_atoi(*line);
		if (reg > REG_NUMBER || reg <= 0)
			return (asm_error(9));
		(*line)++;
		if (reg > 9)
			(*line)++;
		if (reg > 99)
			(*line)++;
		g_pos++;
		if (check == 1)
			return (asm_check_virgule(line));
		return (1);
	}
	return (0);
}

/*
** Check si l'indirect est correct
*/

int		asm_check_ind(char **line, int check)
{
	if (**line == LABEL_CHAR)
	{
		(*line)++;
		while (**line && ft_strchr(LABEL_CHARS, **line))
			(*line)++;
	}
	else if (((**line == '+' || **line == '-') && (*line)++) ||
	ft_isdigit(**line))
	{
		while (ft_isdigit(**line))
			(*line)++;
	}
	else
		return (0);
	if (**line != '\0' && **line != '\n'
		&& **line != SEPARATOR_CHAR && **line != ' ' && **line != '\t')
		return (asm_error(7));
	g_pos = g_pos + 2;
	if (check == 1)
		return (asm_check_virgule(line));
	return (1);
}

/*
** Incrémente line selon l'instruction passé
*/

int		check_valid_line(char *line)
{
	int	fct;

	fct = asm_instruct_name(line);
	if (fct)
		g_pos++;
	if (fct == 1 || fct == 9 || fct == 12 || fct == 14)
		line = line + 4;
	else if (fct == 2 || fct == 3 || fct == 7)
		line = line + 2;
	else if (fct == 15)
		line = line + 5;
	else
		line = line + 3;
	if (fct != 1 && fct != 9 && fct != 12 & fct != 15)
		g_pos++;
	asm_check_arg(&line, fct);
	while (*line && *line != '\n' && *line != COMMENT_CHAR && *line != ';')
		if (*line && *line != ' ' && *line != '\t' && *line != '\n')
			return (asm_error(12));
		else
			line++;
	return (1);
}
