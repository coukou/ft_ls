/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:39:28 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/28 20:06:25 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_get_columns_width(t_list *lst, t_ls_colw *colw)
{
	t_ls_ent *ent;
	int tmp;

	ft_bzero(colw, sizeof(*colw));
	while (lst)
	{
		ent = lst->content;
		if ((tmp = ft_nbrlen(ent->stat->st_nlink, 10)) > colw->lnk)
			colw->lnk = tmp;
		if ((tmp = ft_nbrlen(ent->stat->st_size, 10)) > colw->size)
			colw->size = tmp;
		if ((tmp = ft_strlen(ent->grp_name)) > colw->grp)
			colw->grp = tmp;
		if ((tmp = ft_strlen(ent->usr_name)) > colw->user)
			colw->user = tmp;
		if ((tmp = ft_strlen(ent->date)) > colw->date)
			colw->date = tmp;
		if (ent->stat->st_rdev && (tmp = ft_nbrlen(minor(ent->stat->st_rdev), 10)) > colw->min)
			colw->min = tmp;
		if (ent->stat->st_rdev && (tmp = ft_nbrlen(major(ent->stat->st_rdev), 10)) > colw->maj)
			colw->maj = tmp;
		lst = lst->next;
	}
	if (colw->min > 0 && colw->size < (colw->min + colw->maj + 1))
		colw->size += (colw->min + colw->maj + 1);
	else if (colw->size > (colw->min + colw->maj + 1))
		colw->maj = colw->size - (colw->min + colw->maj);
}

void		ft_ls_format_long_line(t_ls_ent *ent, t_ls_colw *colw, char *color, char *out)
{
	int		i;

	i = 0;
	i += ft_sprintf(out + i, "%s ", ent->flags);
	i += ft_sprintf(out + i, "%*d ", colw->lnk + 1, ent->stat->st_nlink);
	if (*(ent->usr_name) != 0)
		i += ft_sprintf(out + i, "%-*s ", colw->user + 1, ent->usr_name);
	i += ft_sprintf(out + i, "%-*s ", colw->grp + 1, ent->grp_name);
	if (ent->stat->st_rdev > 0)
	{
		i += ft_sprintf(out + i, "%*d, ", colw->maj, major(ent->stat->st_rdev));
		i += ft_sprintf(out + i, "%*d ", colw->min, minor(ent->stat->st_rdev));
	}
	else
		i += ft_sprintf(out + i, "%*d ", colw->size, ent->stat->st_size);
	i += ft_sprintf(out + i, "%*s ", colw->date, ent->date);
	i += ft_sprintf(out + i, "%s%s\033[0m", color, ent->name);
	if (*ent->lnk)
		i += ft_sprintf(out + i, " -> %s", ent->lnk);
}
