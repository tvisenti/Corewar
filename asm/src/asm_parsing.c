/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 18:53:48 by tvisenti          #+#    #+#             */
/*   Updated: 2016/08/29 09:23:28 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Check si le fichier se termine par .s
*/

int			asm_check_champ(char *champ)
{
	int i;

	i = 0;
	while (champ[i])
		i++;
	if (i > 3 && champ[i - 1] == 's' && champ[i - 2] == '.')
		return (1);
	else
		return (asm_error(14));
}

/*
** Mets la ligne valide dans le char *
*/

char		*asm_put_line_in_file(char *line, int i, char *file)
{
	while (line[i] == '\t' || line[i] == ' ')
		i++;
	if (line[i] && line[i] != COMMENT_CHAR && line[i] != ';' &&
	check_valid_line(&line[i]))
		file = asm_free_join(&line[i], file);
	free(line);
	line = NULL;
	return (file);
}

/*
** Récupere le nom du label, position dans une liste chainée
*/

t_label		*asm_parse_line(int fd, char **file)
{
	t_label	*label;
	char	*line;
	int		i;

	label = NULL;
	line = NULL;
	while (!(i = 0) && get_next_line(fd, &line) > 0)
	{
		g_line++;
		while (line[i] == '\t' || line[i] == ' ')
			i++;
		if (line[i] && line[i] != COMMENT_CHAR && line[i] != ';' &&
		asm_check_label(line) >= 1)
		{
			label = asm_label_init(label, line);
			while (line[i] != LABEL_CHAR)
				i++;
			i++;
		}
		*file = asm_put_line_in_file(line, i, *file);
	}
	free(line);
	return (label);
}

void		asm_bonus_champ(t_header *head)
{
	ft_printf("%-15s : %s\n", "Nom du champion", head->prog_name);
	ft_printf("%-15s : %s\n", "Commentaire", head->comment);
}

/*
** Début du parsing
*/

int			asm_parsing(char *champion, t_header *head, int check)
{
	int			fd;
	int			pos;
	char		*file;
	t_label		*label;

	pos = 0;
	label = NULL;
	file = NULL;
	asm_check_champ(champion);
	if ((fd = open(champion, O_RDONLY, 0555)) == -1)
		return (-1);
	asm_handler_name_comment(fd, head);
	if (check == 1)
		asm_bonus_champ(head);
	label = asm_parse_line(fd, &file);
	asm_check_double_label(label);
	if (asm_check_label_exist(label, file) == 0)
		return (asm_error(12));
	asm_reader(label, head, champion, file);
	if (file && file[0])
		free(file);
	if (label)
		asm_free_label(label);
	return (0);
}
