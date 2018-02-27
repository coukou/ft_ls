/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:09:33 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/27 18:16:34 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_ls_get_opt_flag(int c)
{
	if (c == 'l')
		return (FT_LS_OPT_LONG);
	if (c == 'R')
		return (FT_LS_OPT_RECURSIVE);
	if (c == 'a')
		return (FT_LS_OPT_ALL);
	if (c == 'r')
		return (FT_LS_OPT_REVERSE);
	if (c == 't')
		return (FT_LS_OPT_S_MTIME);
	if (c == '1')
		return (FT_LS_OPT_ONE);
	return (0);
}

void		ft_ls_aget_entries(t_ls *ls, t_ls_entries *entries, int ac, char **av)
{
	int			i;
	t_ls_ent	*ent;

	i = -1;
	entries->elst = NULL;
	entries->flst = NULL;
	entries->dlst = NULL;
	while (++i < ac)
	{
		if (*av[i] == '-')
			continue ;
		if ((ent = ft_ls_entnew(ls, av[i])))
			ft_ls_add_entry(ent, entries, 1);
	}
	if (!entries->elst && !entries->flst && !entries->dlst)
	{
		if ((ent = ft_ls_entnew(ls, ".")))
			ft_ls_add_entry(ent, entries, 1);
	}
}

void		ft_ls_aget_opts(t_ls *ls, int ac, char **av)
{
	int i;
	int j;
	int opt;
	char err[256];

	i = -1;
	while (++i < ac)
	{
		j = 0;
		if (av[i][j] == '-')
		{
			while (av[i][++j])
			{
				if (!(opt = ft_ls_get_opt_flag(av[i][j])))
				{
					ft_sprintf(err, "illegal option -- %c\nusage: ft_ls [-lRart1] [file ...]", av[i][j]);
					return ft_ls_exit(ls, err, 1);
				}
				ls->opts |= opt;
			}
		}
	}
}
