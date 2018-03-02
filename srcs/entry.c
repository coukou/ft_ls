/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:17:44 by orenkay           #+#    #+#             */
/*   Updated: 2018/03/02 20:34:55 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_ls_get_ent_letter(t_ls_ent *ent)
{
	int type;

	type = ent->stat->st_mode & S_IFMT;
	if (type == S_IFSOCK)
		return ("s");
	else if (type == S_IFLNK)
		return ("l");
	else if (type == S_IFBLK)
		return ("b");
	else if (type == S_IFDIR)
		return ("d");
	else if (type == S_IFCHR)
		return ("c");
	else if (type == S_IFIFO)
		return ("p");
	else
		return ("-");
}

void		ft_ls_set_flags(t_ls_ent *ent)
{
	int i;
	int m;

	i = 0;
	m = ent->stat->st_mode;
	i += ft_sprintf(ent->flags + i, ft_ls_get_ent_letter(ent));
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IRUSR) ? "r" : "-"));
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IWUSR) ? "w" : "-"));
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IXUSR) ? "x" : "-"));
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IRGRP) ? "r" : "-"));
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IWGRP) ? "w" : "-"));
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IXGRP) ? "x" : "-"));
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IROTH) ? "r" : "-"));
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IWOTH) ? "w" : "-"));
	if (FT_MASK_EQ(m, S_ISVTX))
		i += ft_sprintf(ent->flags + i, "t");
	else
		i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IXOTH) ? "x" : "-"));
}

void		ft_ls_set_grp_name(t_ls_ent *ent)
{
	t_group *grp;

	if ((grp = getgrgid(ent->stat->st_gid)) == 0)
		ft_lltoa(ent->stat->st_gid, 10, ent->grp_name);
	else
		ft_strcpy(ent->grp_name, grp->gr_name);
}

void		ft_ls_set_usr_name(t_ls *ls, t_ls_ent *ent)
{
	t_passwd *pwd;

	if (FT_MASK_EQ(ls->opts, FT_LS_OPT_GRP_ONLY))
		*(ent->usr_name) = 0;
	else if ((pwd = getpwuid(ent->stat->st_uid)) == 0)
		ft_lltoa(ent->stat->st_uid, 10, ent->usr_name);
	else
		ft_strcpy(ent->usr_name, pwd->pw_name);
}

t_ls_ent	*ft_ls_entnew(t_ls *ls, const char *filename, int (*statfn)(const char *restrict, t_stat*))
{
	t_ls_ent	*ent;

	if (!(ent = ft_memalloc(sizeof(*ent))))
		return (NULL);
	ft_strcpy((char*)ent->name, (char*)filename);
	ent->path = ft_strjoin(ls->wpath, ent->name);
	ft_bzero(ent->lnk, sizeof(ent->lnk));
	if (!(ent->stat = ft_memalloc(sizeof(*ent->stat))))
	{
		ft_ls_entdel(ent);
		return (NULL);
	}
	if ((statfn(ent->path, ent->stat) != -1) &&
		FT_MASK_EQ(ls->opts, FT_LS_OPT_LONG))
	{
		if ((ent->stat->st_mode & S_IFMT) == S_IFLNK)
			readlink(ent->path, ent->lnk, sizeof(ent->lnk) - 1);
		ft_ls_set_grp_name(ent);
		ft_ls_set_usr_name(ls, ent);
		ft_ls_set_flags(ent);
		ft_ls_set_date(ls, ent);
	}
	return (ent);
}
