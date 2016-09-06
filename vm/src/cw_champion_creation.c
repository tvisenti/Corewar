/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_champion_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/09/01 18:11:10 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int				cw_find_num(t_proc *proc, int c_nb)
{
	t_champion	tmp;
	int			i;

	i = 0;
	tmp = proc->champions[i];
	while (tmp.num)
	{
		if (tmp.num == c_nb)
		{
			c_nb++;
			i = 0;
			tmp = proc->champions[i];
		}
		else
			tmp = proc->champions[++i];
	}
	return (c_nb);
}

int				cw_chk_champions(t_proc *proc, int i)
{
	t_champion	champ;

	champ = proc->champions[i];
	if (champ.header->magic != COREWAR_EXEC_MAGIC)
		return (cw_error_msg("Wrong magic number"));
	if (champ.header->prog_size > CHAMP_MAX_SIZE)
		return (cw_error_msg("a champion is too fat"));
	return (1);
}

int				cw_get_header(t_proc *proc, int fd, int c_nb, int n)
{
	t_header	*header;
	t_champion	new;
	int			i;

	i = 0;
	if ((header = malloc(sizeof(t_header))) == NULL)
		return (cw_error_msg("failed to malloc the header"));
	if (read(fd, header, sizeof(t_header)) == -1)
		return (cw_error_msg("failed to read the header"));
	header->prog_size = cw_invert_endian(header->prog_size);
	header->magic = cw_invert_endian(header->magic);
	while (proc->champions[i].num)
		i++;
	proc->champions[i].header = header;
	proc->champions[i].id_champion = i ? proc->champions[i - 1].id_champion + 1
	: 1;
	return (cw_chk_champions(proc, i));
}

int				cw_create_champion(char *file, int c_nb, t_proc *proc, int n)
{
	int			fd;
	int			chk;
	t_champion	c_in_load;
	int			i;

	i = 0;
	if ((fd = open(file, O_RDONLY, 0555)) == -1)
		return (cw_error_msg("failed to open the champion file"));
	if ((chk = cw_get_header(proc, fd, c_nb, n)) == 0)
		return (0);
	c_nb = n ? c_nb : cw_find_num(proc, c_nb);
	while (proc->champions[i].num)
		i++;
	proc->champions[i].num = c_nb;
	if (chk && (proc->champions[i].insert =
		malloc(proc->champions[i].header->prog_size)) == NULL)
		return (cw_error_msg("failed to malloc instruction failed"));
	if (read(fd, proc->champions[i].insert,
		proc->champions[i].header->prog_size) == -1)
		return (cw_error_msg("failed to load instructions"));
	proc->nb_proc = i + 1;
	if (close(fd) == -1)
		return (cw_error_msg("failed to close the file"));
	return (chk);
}
