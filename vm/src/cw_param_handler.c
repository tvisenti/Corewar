/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_param_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 15:54:35 by ademenet          #+#    #+#             */
/*   Updated: 2016/08/31 19:14:01 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

long	cw_cnb_chk(long c_nb, t_proc *proc, char *str)
{
	t_champion		tmp;
	int				cur;
	int				i;

	i = 0;
	tmp = proc->champions[i];
	cur = -1;
	while (str[++cur])
		if (!isdigit(str[cur]) && str[0] != '-')
			return (cw_error_msg("The player number is not valid"));
	if (c_nb <= 0)
		return (cw_error_msg("The player number musn't be negative or nil"));
	while (tmp.num)
	{
		if (tmp.num == c_nb)
			return (cw_error_msg("Number already assigned to a player"));
		i++;
		tmp = proc->champions[i];
	}
	return (1);
}

int		cw_crea_step(int n[2], t_proc *proc, char **av, int c_nb)
{
	int				i;

	i = 0;
	if (!n[0])
	{
		if (cw_create_champion(av[n[1]], c_nb, proc, 0) <= 0)
			return (cw_error_msg("Wrong champion file !"));
	}
	else if (cw_create_champion(av[n[1]], n[0], proc, 1) <= 0)
		return (cw_error_msg("Wrong champion file !"));
	while (proc->champions[i].num != 0)
		i++;
	if (i > MAX_PLAYERS)
		return (cw_error_msg("Too much players"));
	return (1);
}

int		cw_param_loop(int param, int ac, char **av, t_proc *proc)
{
	long			n;
	unsigned int	c_nb;
	int				tab[2];

	c_nb = 0;
	while ((n = 0) || (++param < ac && !(av[param][0] == '-' &&
			av[param][1] != 'n' && ft_isalpha(av[param][1]))))
	{
		if (ft_strcmp(av[param], "-n") == 0)
		{
			if (++param >= ac)
				return (cw_error_msg("The player number is not valid"));
			if (!cw_cnb_chk(n = ft_atoi(av[param]), proc, av[param]))
				return (0);
			if (++param >= ac)
				return (cw_error_msg("Wrong format"));
		}
		else
			c_nb++;
		tab[0] = n;
		tab[1] = param;
		if (!cw_crea_step(tab, proc, av, c_nb))
			return (0);
	}
	return (proc->champions[0].num == 0 ? cw_error_msg("Wrong format") : param);
}

int		cw_param_fst_chk(int ac, int param, char **av, t_proc *proc)
{
	int				n;

	n = -1;
	if (ac < 2)
		return (cw_error_msg("Too few parameters"));
	if (ft_strcmp(av[param], "-dump") == 0)
	{
		if (av[++param] == NULL || (n = ft_atoi(av[param])) <= 0)
			return (cw_error_msg("'dump' must have a valid value"));
		proc->dump = n;
	}
	return (1);
}

int		cw_param(char **av, int ac, t_proc *proc)
{
	long			n;
	int				param;
	unsigned int	c_nb;

	n = 0;
	param = 0;
	c_nb = 0;
	if (!cw_param_fst_chk(ac, 1, av, proc))
		return (0);
	param = proc->dump ? param + 2 : param;
	if (!(param = cw_param_loop(param, ac, av, proc)))
		return (0);
	cw_bon_handler(av, ac, param);
	return (1);
}
