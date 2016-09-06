/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 19:16:43 by tvisenti          #+#    #+#             */
/*   Updated: 2016/08/01 18:17:15 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

t_header	*asm_header_init(void)
{
	t_header	*new;

	if (!(new = (t_header*)malloc(sizeof(t_header))))
		return (NULL);
	if (new != NULL)
	{
		new->magic = COREWAR_EXEC_MAGIC;
		new->prog_size = 0;
		ft_bzero(new->prog_name, PROG_NAME_LENGTH);
		ft_bzero(new->comment, COMMENT_LENGTH);
	}
	return (new);
}

t_label		*asm_label_init(t_label *label, char *line)
{
	t_label		*new;
	int			len;

	len = 0;
	if (!(new = malloc(sizeof(t_label))))
		return (NULL);
	while (line[len] != LABEL_CHAR)
		len++;
	new->name = NULL;
	new->next = NULL;
	new->pos = 0;
	new->name = ft_strsub(line, 0, len);
	new->pos = g_pos;
	new->next = label;
	return (new);
}
