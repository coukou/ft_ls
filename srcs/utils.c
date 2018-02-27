/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:18:07 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/27 18:13:02 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_clean(t_ls *ls)
{
	ft_strdel(&ls->wpath);
}

void		ft_ls_exit(t_ls *ls, const char *msg, int exit_code)
{
	ft_ls_clean(ls);
	if (msg)
		ft_printf("ft_ls: %s\n", msg);
	exit(exit_code);
}
