/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:26:57 by orenkay           #+#    #+#             */
/*   Updated: 2018/03/02 15:36:41 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_sort_alpha(void *a, void *b)
{
	return (ft_strcmp(((t_ls_ent*)a)->name, ((t_ls_ent*)b)->name));
}

int		ft_ls_sort_mtime(void *a, void *b)
{
	time_t a_value;
	time_t b_value;

	a_value = ((t_ls_ent*)a)->stat->st_mtime;
	b_value = ((t_ls_ent*)b)->stat->st_mtime;
	if (a_value == b_value)
		return (ft_ls_sort_alpha(a, b));
	return (a_value > b_value) ? -1 : 1;
}

int		ft_ls_sort_atime(void *a, void *b)
{
	time_t	a_value;
	time_t	b_value;

	a_value = ((t_ls_ent*)a)->stat->st_atime;
	b_value = ((t_ls_ent*)b)->stat->st_atime;
	if (a_value == b_value)
		return (ft_ls_sort_alpha(a, b));
	return (a_value > b_value) ? -1 : 1;
}

int		ft_ls_sort_size(void *a, void *b)
{
	off_t	a_value;
	off_t	b_value;

	a_value = ((t_ls_ent*)a)->stat->st_size;
	b_value = ((t_ls_ent*)b)->stat->st_size;
	if (a_value == b_value)
		return (ft_ls_sort_alpha(a, b));
	return (a_value > b_value) ? -1 : 1;
}

void	ft_ls_get_sortfn(t_ls *ls, int (**out)(void*, void*))
{
	if (FT_MASK_EQ(ls->opts, FT_LS_OPT_S_BIRTH) &&
		FT_MASK_EQ(ls->opts, FT_LS_OPT_S_MTIME))
		*out = &ft_ls_sort_birth;
	else if (FT_MASK_EQ(ls->opts, FT_LS_OPT_S_ATIME) &&
		FT_MASK_EQ(ls->opts, FT_LS_OPT_S_MTIME))
		*out = &ft_ls_sort_atime;
	else if (FT_MASK_EQ(ls->opts, FT_LS_OPT_S_MTIME))
		*out = &ft_ls_sort_mtime;
	else if (FT_MASK_EQ(ls->opts, FT_LS_OPT_S_SIZE))
		*out = &ft_ls_sort_size;
	else
		*out = &ft_ls_sort_alpha;
}
