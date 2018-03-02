/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:42:27 by spopieul          #+#    #+#             */
/*   Updated: 2018/03/02 20:32:01 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_entdel(t_ls_ent *ent)
{
	if (ent->path != NULL)
		ft_memdel((void**)&ent->path);
	if (ent->stat != NULL)
		ft_memdel((void**)&ent->stat);
	free(ent);
}

t_ls_ent	*ft_ls_entdup(t_ls_ent *ent)
{
	t_ls_ent *dup;

	if (!(dup = ft_memalloc(sizeof(*ent))))
		return (NULL);
	ft_memcpy(dup, ent, sizeof(*ent));
	dup->path = ft_strdup(ent->path);
	dup->stat = ft_memalloc(sizeof(*dup->stat));
	ft_memcpy(dup->stat, ent->stat, sizeof(*dup->stat));
	return (dup);
}

void		ft_ls_add_err_entry(t_ls_ent *ent, t_ls_entries *entries)
{
	char	*err;

	err = ft_ls_get_ent_error(ent);
	ft_lstadd(&entries->elst, ft_lstnew(err, ft_strlen(err) + 1));
	ft_strdel(&err);
	ft_ls_entdel(ent);
}

void		ft_ls_add_dir_entry(t_ls *ls, t_ls_ent *ent,
								t_ls_entries *entries, int start)
{
	t_ls_ent	*dir;

	if (!start)
	{
		if (!ft_strequ(ent->name, ".") && !ft_strequ(ent->name, "..") &&
			FT_MASK_EQ(ls->opts, FT_LS_OPT_RECURSIVE) &&
			!FT_MASK_EQ(ls->opts, FT_LS_OPT_D))
		{
			if ((dir = ft_ls_entdup(ent)))
			{
				ft_lstadd_back(&entries->dlst, ft_lstnew(dir, sizeof(*ent)));
				free(dir);
			}
		}
	}
	else
		ft_lstadd_back(&entries->dlst, ft_lstnew(ent, sizeof(*ent)));
}

void		ft_ls_add_entry(t_ls *ls, t_ls_ent *ent,
							t_ls_entries *entries, int start)
{
	if ((ent->stat->st_mode & S_IFMT) == S_IFDIR)
		ft_ls_add_dir_entry(ls, ent, entries, start);
	if ((ent->stat->st_mode & S_IFMT) == 0)
		ft_ls_add_err_entry(ent, entries);
	else
	{
		if (start && (ent->stat->st_mode & S_IFMT) == S_IFDIR)
		{
			free(ent);
			return ;
		}
		ft_lstadd_back(&entries->flst, ft_lstnew(ent, sizeof(*ent)));
		free(ent);
	}
}
