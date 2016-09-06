/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 19:08:37 by tvisenti          #+#    #+#             */
/*   Updated: 2016/08/29 11:34:07 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Error
*/

int		asm_error_sec(int error)
{
	if (error == 11)
		ft_printf("Impossible to find name or comment\n");
	if (error == 12)
		ft_printf("No argument (or too much...) for instruction -> line: %d\n",
		g_line);
	if (error == 13)
		ft_printf("Error multiple lines on name or comment\n");
	if (error == 14)
		ft_printf("Wrong file extension\n");
	if (error == 15)
		ft_printf("Damn it, you forgot a LABEL_CHAR\n");
	exit(0);
	return (0);
}

int		asm_error(int error)
{
	if (error == 1)
		ft_printf("Wrong format name -> line: %d\n", g_line);
	if (error == 2)
		ft_printf("Wrong format comment -> line: %d\n", g_line);
	if (error == 3)
		ft_printf("Wrong format labels_char -> line: %d\n", g_line);
	if (error == 4)
		ft_printf("Wrong format label_char -> line: %d\n", g_line);
	if (error == 5)
		ft_printf("Wrong name of instruct -> line: %d\n", g_line);
	if (error == 7)
		ft_printf("Not an indirect -> line: %d\n", g_line);
	if (error == 8)
		ft_printf("Arguments Problem, Bro -> line: %d\n", g_line);
	if (error == 9)
		ft_printf("There's same label\n");
	if (error == 10)
		ft_printf("No match between label\n");
	return (asm_error_sec(error));
}
