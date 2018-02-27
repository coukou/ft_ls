/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:26:57 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/26 18:33:21 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_sort_alpha(void *a, void *b)
{
	return (ft_strcmp(((t_ls_ent*)a)->name, ((t_ls_ent*)b)->name));
}

int		ft_ls_sortr_alpha(void *a, void *b)
{
	return (ft_ls_sort_alpha(b, a));
}

int		ft_ls_sort_mtime(void *a, void *b)
{
	time_t atime;
	time_t btime;

	atime = ((t_ls_ent*)a)->stat->st_mtime;
	btime = ((t_ls_ent*)b)->stat->st_mtime;
	if (atime == btime)
		return (ft_ls_sort_alpha(a, b));
	return (atime > btime) ? -1 : 1;
}

int		ft_ls_sortr_mtime(void *a, void *b)
{
	return (ft_ls_sort_mtime(b, a));
}

void	ft_ls_init_sortfn(t_ls *ls)
{
	int reverse;

	reverse = FT_MASK_EQ(ls->opts, FT_LS_OPT_REVERSE);
	if (FT_MASK_EQ(ls->opts, FT_LS_OPT_S_MTIME))
		ls->sortfn = (!reverse) ? &ft_ls_sort_mtime : &ft_ls_sortr_mtime;
	else
		ls->sortfn = (!reverse) ? &ft_ls_sort_alpha : &ft_ls_sortr_alpha;
}
