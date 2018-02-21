/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:29:26 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/21 22:11:19 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ls_alpha_sort(void *a, void *b)
{
	return (ft_strcmp(((t_ls_file*)a)->name, ((t_ls_file*)b)->name));
}

static int	ls_alpha_sort_rev(void *a, void *b)
{
	return (ls_alpha_sort(b, a));
}

static int	ls_mtime_sort(void *a, void *b)
{
	time_t atime;
	time_t btime;

	atime = ((t_ls_file*)a)->stat->st_mtime;
	btime = ((t_ls_file*)b)->stat->st_mtime;
	if (atime == btime)
		return (ls_alpha_sort(a, b));
	return (atime > btime) ? -1 : 1;
}

static int	ls_mtime_sort_rev(void *a, void *b)
{
	return (ls_mtime_sort(b, a));
}

void		ls_init_sortfn(t_ls_state *state)
{
	int reverse;

	reverse = FT_MASK_EQ(state->opts, FT_LS_OPT_REVERSE);
	if (FT_MASK_EQ(state->opts, FT_LS_OPT_S_MTIME))
		state->sortfn = (!reverse) ? &ls_mtime_sort : &ls_mtime_sort_rev;
	else
		state->sortfn = (!reverse) ? &ls_alpha_sort : &ls_alpha_sort_rev;
}
