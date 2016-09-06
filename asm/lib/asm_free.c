/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Transmet <Transmet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 16:13:52 by Transmet          #+#    #+#             */
/*   Updated: 2016/08/25 17:01:33 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

/*
** Return 1 si le header est complet, si non complet 0 ou alors error
*/

int			asm_ret_header(t_header *head, char *line)
{
	if (head->comment[0] && head->prog_name[0])
	{
		if (ft_strrchr(line, '"') != ft_strchr(line, '"'))
		{
			free(line);
			line = NULL;
			return (1);
		}
		return (asm_error(13));
	}
	return (0);
}

/*
** Free la liste label
*/

int			asm_free_label(t_label *label)
{
	t_label	*nxt;

	nxt = label->next;
	while (nxt)
	{
		label->next = NULL;
		free(label->name);
		free(label);
		label = nxt;
		nxt = label->next;
	}
	free(label->name);
	free(label);
	return (1);
}

/*
** Free le tableau
*/

int			asm_free_tab(char **tab, int ret)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			i++;
			free(tab[i - 1]);
		}
		free(tab);
	}
	return (ret);
}

/*
** Fonction qui realloc pour recuperer tout le fichier .s
*/

char		*asm_realloc(char *line, char *file, int i)
{
	int		len;
	char	*tmp;
	char	*sub;

	len = 0;
	tmp = NULL;
	sub = NULL;
	sub = ft_strsub(line, i, ft_strlen(line) - i);
	tmp = malloc(sizeof(char) * (ft_strlen(file) + ft_strlen(sub) + 1));
	tmp = ft_strcpy(tmp, file);
	tmp = ft_strcat(tmp, sub);
	free(file);
	free(sub);
	file = NULL;
	sub = NULL;
	while (tmp[len])
		len++;
	tmp[len] = '\n';
	tmp[len + 1] = '\0';
	file = ft_strdup(tmp);
	free(tmp);
	return (file);
}

char		*asm_free_join(char *line, char *file)
{
	int		i;
	int		len;
	char	*sub;

	i = 0;
	sub = NULL;
	if (line[i])
	{
		if (!(len = 0) && !file)
		{
			sub = ft_strsub(line, i, ft_strlen(line) - i);
			file = malloc(sizeof(char) * (ft_strlen(sub) + 1));
			file = ft_strcpy(file, sub);
			while (file[len])
				len++;
			file[len] = '\n';
			file[len + 1] = '\0';
			free(sub);
			sub = NULL;
		}
		else
			file = asm_realloc(line, file, i);
	}
	return (file);
}
