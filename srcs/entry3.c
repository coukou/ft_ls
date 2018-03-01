/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:56:22 by spopieul          #+#    #+#             */
/*   Updated: 2018/03/01 13:38:08 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_set_date(t_ls *ls, t_ls_ent *ent)
{
	char	*tmp;
	time_t	t;

	if (FT_MASK_EQ(ls->opts, FT_LS_OPT_S_BIRTH))
		t = ent->stat->st_birthtime;
	else if (FT_MASK_EQ(ls->opts, FT_LS_OPT_S_ATIME))
		t = ent->stat->st_atime;
	else
		t = ent->stat->st_mtime;
	tmp = ctime(&t);
	if ((time(NULL) - t) >= (FT_LS_MONTH_TIME * 6))
		ft_sprintf(ent->date, "%.4s%.3s%5.4s", tmp + 4, tmp + 8, tmp + 20);
	else
		ft_sprintf(ent->date, "%.4s%.3s%5.5s", tmp + 4, tmp + 8, tmp + 11);
}

int		ft_ls_get_dir_entries(t_ls *ls, const char *path, t_ls_entries *entries)
{
	t_ls_ent	*ent;
	DIR			*dir;
	t_dirent	*tmp;

	ft_ls_set_path(ls, path);
	if(!(dir = opendir(path)))
	{
		ft_printf("ft_ls: cannot open directory '%s': %s\n", path, strerror(errno));
		ls->error = (ls->error > 0) ? ls->error : 1;
		return (0);
	}
	while ((tmp = readdir(dir)))
	{
		if (!FT_MASK_EQ(ls->opts, FT_LS_OPT_ALL) && *(tmp->d_name) == '.')
			continue ;
		if ((ent = ft_ls_entnew(ls, tmp->d_name)))
			ft_ls_add_entry(ls, ent, entries, 0);
	}
	closedir(dir);
	ft_ls_sort_entries(ls, entries);
	return (1);
}
