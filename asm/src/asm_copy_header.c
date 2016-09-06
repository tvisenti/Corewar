/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_copy_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 10:20:25 by tvisenti          #+#    #+#             */
/*   Updated: 2016/08/25 17:06:23 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Bouge le pointeur juste avant le nom ou le commentaire
*/

int			asm_header_pass(char *line, int name, int com, int check)
{
	int	i;

	if (check)
		i = name;
	else
		i = com;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '"')
		return (0);
	i++;
	return (i);
}

int			asm_header_pass_end(char *line, int i)
{
	while (line[i] && line[i] != '"')
		i++;
	if (line[i] == '"')
		i++;
	while (line[i] && line[i] != '\n' && i++)
		if (line[i] && line[i] != ' ' && line[i] != '\t')
			return (asm_error(1));
	return (0);
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

t_header	*asm_copy_header(char *line, t_header *head, int check)
{
	char *tmp;

	tmp = NULL;
	if (check == 0)
	{
		tmp = ft_strsub(line, 0, ft_strclen(line, '"'));
		ft_strncat(head->prog_name, tmp, PROG_NAME_LENGTH);
	}
	if (check == 1)
	{
		if (line[0] == '"')
			ft_strcpy(head->comment, "I don't need a comment to crush you");
		else
		{
			tmp = ft_strsub(line, 0, ft_strclen(line, '"'));
			ft_strncat(head->comment, tmp, COMMENT_LENGTH);
		}
	}
	if (tmp != NULL)
		free(tmp);
	tmp = NULL;
	return (head);
}

int			asm_copy_name_comment(char *line, t_header *head, int name, int com)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!head->prog_name[0] && ft_strncmp(NAME_CMD_STRING, line, name) == 0)
	{
		if ((i = asm_header_pass(line, name, com, 1)) == 0)
			return (asm_error(1));
		else
			asm_copy_header(&line[i], head, 0);
	}
	else if (!head->comment[0] &&
		ft_strncmp(COMMENT_CMD_STRING, line, com) == 0)
	{
		if ((i = asm_header_pass(line, name, com, 0)) == 0)
			return (asm_error(11));
		else
			head = asm_copy_header(&line[i], head, 1);
	}
	else
		return (asm_error(11));
	return (asm_header_pass_end(line, i));
}

/*
** Récupére le nom et le comment et le stocke dans la struct(header)
*/

int			asm_handler_name_comment(int fd, t_header *head)
{
	int		i;
	char	*line;

	i = 0;
	line = 0;
	while (get_next_line(fd, &line) > 0)
	{
		g_line++;
		if (line[0] != COMMENT_CHAR && line[0] != ';' && line[0] != '\0')
		{
			while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
				i++;
			asm_copy_name_comment(&line[i], head, ft_strlen(NAME_CMD_STRING),
			ft_strlen(COMMENT_CMD_STRING));
			if (asm_ret_header(head, line) == 1)
				return (1);
		}
		free(line);
		line = NULL;
	}
	return (asm_error(11));
}
