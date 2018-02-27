/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:17:44 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/26 20:34:30 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_ls_get_ent_error(t_ls_ent *ent)
{
	char *ret;
	char *err;
	size_t size;

	err = strerror(errno);
	size = 0;
	size += ft_strlen(ent->name);
	size += ft_strlen(": ");
	size += ft_strlen(err);
	ret = ft_strnew(size);
	ft_sprintf(ret, "%s: %s", ent->name, err);
	return (ret);
}

void		ft_ls_entdel(t_ls_ent *ent)
{
	if (ent->path != NULL)
		ft_memdel((void**)&ent->path);
	if (ent->stat != NULL)
		ft_memdel((void**)&ent->stat);
	ft_memdel((void**)&ent);
}

void		ft_ls_add_err_entry(t_ls_ent *ent, t_ls_entries *entries)
{
	char	*err;

	err = ft_ls_get_ent_error(ent);
	ft_lstadd(&entries->elst, ft_lstnew(err, ft_strlen(err)));
	ft_strdel(&err);
	ft_ls_entdel(ent);
}

void		ft_ls_add_entry(t_ls_ent *ent, t_ls_entries *entries, int start)
{

	if ((ent->stat->st_mode & S_IFMT) == 0)
		ft_ls_add_err_entry(ent, entries);
	else if ((ent->stat->st_mode & S_IFMT) == S_IFDIR)
	{
		if (!start)
		{

			if (!ft_strequ(ent->name, ".") && !ft_strequ(ent->name, ".."))
				ft_lstadd(&entries->dlst, ft_lstnew(ent->path, ft_strlen(ent->path) + 1));
			ft_lstadd(&entries->flst, ft_lstnew(ent, sizeof(*ent)));
			free(ent);
		}
		else
		{
			ft_lstadd(&entries->dlst, ft_lstnew(ent->path, ft_strlen(ent->path) + 1));
			ft_ls_entdel(ent);
		}
	}
	else
	{
		ft_lstadd(&entries->flst, ft_lstnew(ent, sizeof(*ent)));
		free(ent);
	}
}

void		ft_ls_clean_entries(t_ls_entries *entries)
{
	if (entries->elst)
		ft_lstdel(&entries->elst, (void(*)(void*,size_t))&free);
	if (entries->flst)
		ft_lstdel(&entries->flst, (void(*)(void*,size_t))&ft_ls_entdel);
	if (entries->dlst)
		ft_lstdel(&entries->dlst, (void(*)(void*,size_t))&free);
}

void	ft_ls_set_date(t_ls_ent *ent)
{
	char *tmp;

	tmp = ctime(&ent->stat->st_mtime);
	ft_sprintf(ent->date, "%.4s%.3s%.5s", tmp + 4, tmp + 8, tmp + 11);
}

char	*ft_ls_get_ent_letter(t_ls_ent *ent)
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

void	ft_ls_set_flags(t_ls_ent *ent)
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
	i += ft_sprintf(ent->flags + i, (FT_MASK_EQ(m, S_IXOTH) ? "x" : "-"));
}

t_ls_ent	*ft_ls_entnew(t_ls *ls, const char *filename)
{
	t_ls_ent *ent;
	int ret;

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
	lstat(ent->path, ent->stat);
	if (FT_MASK_EQ(ls->opts, FT_LS_OPT_LONG))
	{
		ent->grp = getgrgid(ent->stat->st_gid);
		ent->pwd = getpwuid(ent->stat->st_uid);
		if ((ent->stat->st_mode & S_IFMT) == S_IFLNK)
			readlink(ent->path, ent->lnk, sizeof(ent->lnk) - 1);
		ft_ls_set_flags(ent);
		ft_ls_set_date(ent);
	}
	return (ent);
}
