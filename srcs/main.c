/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:25:28 by orenkay           #+#    #+#             */
/*   Updated: 2018/03/03 17:12:08 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_ls_init(t_ls *ls, t_ls_entries *entries, int ac, char **av)
{
	int i;

	ls->opts = 0;
	ls->error = 0;
	ls->wpath = ft_strnew(0);
	ft_ls_init_colors(ls);
	i = ft_ls_aget_opts(ls, ac, av);
	if (!ls->wpath)
		ft_ls_exit(ls, "init: something wrong happened", 2);
	ft_ls_aget_entries(ls, entries, ac - i, av + i);
}

static void		ft_ls_start(t_ls *ls, t_ls_entries *entries)
{
	int print_path;

	if (entries->dlst)
		print_path = (entries->elst || entries->flst || entries->dlst->next);
	if (entries->elst)
	{
		ls->error = 2;
		ft_ls_print_err(ls, &entries->elst);
	}
	if (entries->flst)
		ft_ls_print_files(ls, &entries->flst);
	if (entries->dlst)
		ft_ls_print_dir(ls, &entries->dlst, print_path);
}

int				main(int ac, char **av)
{
	t_ls			ls;
	t_ls_entries	entries;

	ft_ls_init(&ls, &entries, ac - 1, av + 1);
	ft_ls_start(&ls, &entries);
	ft_ls_clean(&ls);
	return (ls.error);
}
