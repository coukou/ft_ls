/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:18:07 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/28 21:16:00 by spopieul         ###   ########.fr       */
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

void	ft_ls_set_path(t_ls *ls, const char *path)
{
	char *tmp;

	tmp = ft_strjoin(path, "/");
	ft_strdel(&ls->wpath);
	ls->wpath = tmp;
}

int		ft_ls_get_block_total(t_list *lst)
{
	int res;

	res = 0;
	while (lst)
	{
		res += ((t_ls_ent*)lst->content)->stat->st_blocks;
		lst = lst->next;
	}
	return (res);
}

int		ft_ls_get_column_width(t_list *lst)
{
	int width;
	int tmp;

	width = 0;
	while (lst)
	{
		tmp = ft_strlen(((t_ls_ent*)lst->content)->name);
		if (tmp > width)
			width = tmp;
		lst = lst->next;
	}
	return (width);
}
