/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:44:50 by spopieul          #+#    #+#             */
/*   Updated: 2018/03/01 15:34:15 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_sort_birth(void *a, void *b)
{
	// time_t	a_value;
	// time_t	b_value;

	// a_value = ((t_ls_ent*)a)->stat->st_birthtime;
	// b_value = ((t_ls_ent*)b)->stat->st_birthtime;
	// if (a_value == b_value)
	// 	return (ft_ls_sort_alpha(a, b));
	// return (a_value > b_value) ? -1 : 1;
}

void		ft_ls_sort_entries(t_ls *ls, t_ls_entries *entries)
{
	int (*sort)(void*, void*);
	int reverse;

	ft_lst_mergesort(&entries->elst, 0, &ft_ls_sort_alpha);
	if (FT_MASK_EQ(ls->opts, FT_LS_OPT_F))
		return ;
	reverse = FT_MASK_EQ(ls->opts, FT_LS_OPT_REVERSE);
	sort = ft_ls_get_sortfn(ls);
	ft_lst_mergesort(&entries->flst, reverse, sort);
	ft_lst_mergesort(&entries->dlst, reverse, sort);
}
