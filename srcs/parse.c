/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:09:33 by orenkay           #+#    #+#             */
/*   Updated: 2018/03/05 18:24:50 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_ls_get_opt_flag(int c)
{
	if (c == 'R')
		return (FT_LS_OPT_RECURSIVE);
	if (c == 'S')
		return (FT_LS_OPT_S_SIZE);
	if (c == 'U')
		return (FT_LS_OPT_S_BIRTH);
	if (c == 'a')
		return (FT_LS_OPT_ALL);
	if (c == 'd')
		return (FT_LS_OPT_D);
	if (c == 'f')
		return (FT_LS_OPT_F + FT_LS_OPT_ALL);
	if (c == 'g')
		return (FT_LS_OPT_GRP_ONLY);
	if (c == 'l')
		return (FT_LS_OPT_LONG);
	if (c == 'r')
		return (FT_LS_OPT_REVERSE);
	if (c == 't')
		return (FT_LS_OPT_S_MTIME);
	if (c == 'u')
		return (FT_LS_OPT_S_ATIME);
	if (c == 'G')
		return (FT_LS_OPT_COLOR);
	return (0);
}

void		ft_ls_aget_entries(t_ls *ls, t_ls_entries *entries,
									int ac, char **av)
{
	int			i;
	t_ls_ent	*ent;

	i = -1;
	entries->elst = NULL;
	entries->flst = NULL;
	entries->dlst = NULL;
	while (++i < ac)
	{
		if ((ent = ft_ls_entnew(ls, av[i], &stat)))
			ft_ls_add_entry(ls, ent, entries, 1);
	}
	if (!entries->elst && !entries->flst && !entries->dlst)
	{
		if ((ent = ft_ls_entnew(ls, ".", &lstat)))
			ft_ls_add_entry(ls, ent, entries, 1);
	}
	ft_ls_sort_entries(ls, entries);
}

int			ft_ls_aget_opts(t_ls *ls, int ac, char **av)
{
	int		i;
	int		j;
	int		opt;
	char	err[256];

	i = -1;
	while (++i < ac)
	{
		j = 0;
		if (av[i][j] != '-' || !av[i][j + 1])
			break ;
		while (av[i][++j])
		{
			if (!(opt = ft_ls_get_opt_flag(av[i][j])))
			{
				ft_sprintf(err,
					"illegal option -- %c\nusage: ft_ls [-%s] [file ...]",
					av[i][j], FT_LS_USAGE_STR);
				ft_ls_exit(ls, err, 1);
			}
			ls->opts |= opt;
		}
	}
	return (i);
}
