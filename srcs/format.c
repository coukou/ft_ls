/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:39:28 by spopieul          #+#    #+#             */
/*   Updated: 2018/03/03 14:08:11 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_get_columns_width(t_list *lst, t_ls_colw *colw)
{
	t_ls_ent *ent;

	ft_bzero(colw, sizeof(*colw));
	while (lst)
	{
		ent = lst->content;
		colw->lnk = FT_MAX(ft_nbrlen(ent->stat->st_nlink, 10), colw->lnk);
		colw->size = FT_MAX(ft_nbrlen(ent->stat->st_size, 10), colw->size);
		colw->grp = FT_MAX(ft_strlen(ent->grp_name), colw->grp);
		colw->user = FT_MAX(ft_strlen(ent->usr_name), colw->user);
		colw->date = FT_MAX(ft_strlen(ent->date), colw->date);
		if (ent->stat->st_rdev)
			colw->maj = FT_MAX(ft_nbrlen(major(ent->stat->st_rdev), 10),
								colw->maj);
		if (ent->stat->st_rdev)
			colw->size = FT_MAX(ft_nbrlen(minor(ent->stat->st_rdev), 10),
								colw->size);
		lst = lst->next;
	}
}

void		ft_ls_format_long_line(t_ls_ent *ent, t_ls_colw *colw,
									char *color, char *out)
{
	out += ft_sprintf(out, "%s ", ent->flags);
	out += ft_sprintf(out, "%*d ", colw->lnk + 1, ent->stat->st_nlink);
	if (*ent->usr_name)
		out += ft_sprintf(out, "%-*s ", colw->user + 1, ent->usr_name);
	out += ft_sprintf(out, "%-*s", colw->grp, ent->grp_name);
	if (ent->stat->st_rdev)
	{
		out += ft_sprintf(out, "%*d, ", colw->maj, major(ent->stat->st_rdev));
		out += ft_sprintf(out, "%*d ", colw->size, minor(ent->stat->st_rdev));
	}
	else
	{
		out += ft_sprintf(out, "%*ld ", (colw->size + colw->maj + 2),
			ent->stat->st_size);
	}
	out += ft_sprintf(out, "%*s ", colw->date, ent->date);
	out += ft_sprintf(out, "%s%s\033[0m", color, ent->name);
	if (*ent->lnk)
		out += ft_sprintf(out, " -> %s", ent->lnk);
}
