/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:25:28 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/27 18:51:03 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_ls_init(t_ls *ls, t_ls_entries *entries, int ac, char **av)
{
	ls->opts = 0;
	ls->error = 0;
	ls->wpath = ft_strnew(0);
	ls->term_width = 0;
	ft_ls_aget_opts(ls, ac - 1, av + 1);
	if (!ls->wpath)
		ft_ls_exit(ls, "init: something wrong happened", 2);
	ft_ls_aget_entries(ls, entries, ac - 1, av + 1);
	ft_ls_init_sortfn(ls);
}

static void		ft_ls_print_err(t_ls *ls, t_list **lst)
{
	t_list	*tmp;

	ft_lst_mergesort(lst, &ft_ls_sort_alpha);
	tmp = *lst;
	while (tmp)
	{
		ft_printf("ft_ls: %s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
}

static void		ft_ls_set_path(t_ls *ls, const char *path)
{
	char *tmp;

	tmp = ft_strjoin(path, "/");
	ft_strdel(&ls->wpath);
	ls->wpath = tmp;
}

static int		ft_ls_get_dir_entries(t_ls *ls, const char *path, t_ls_entries *entries)
{
	t_ls_ent	*ent;
	DIR			*dir;
	t_dirent	*tmp;

	entries->elst = NULL;
	entries->flst = NULL;
	entries->dlst = NULL;
	ft_ls_set_path(ls, path);
	if(!(dir = opendir(path)))
	{
		ft_printf("ft_ls: cannot open directory '%s': ", path);
		ls->error = (ls->error > 0) ? ls->error : 1;
		perror(NULL);
		return (0);
	}
	while ((tmp = readdir(dir)))
	{
		if (!FT_MASK_EQ(ls->opts, FT_LS_OPT_ALL) && *(tmp->d_name) == '.')
			continue ;
		ft_printf("DEBUG: %s, %d\n", tmp->d_name, tmp->d_type);
		if ((ent = ft_ls_entnew(ls, tmp->d_name)))
			ft_ls_add_entry(ent, entries, 0);
	}
	closedir(dir);
	return (1);
}

static void		ft_ls_print_files_short(t_ls *ls, t_list *lst)
{
	t_ls_ent	*ent;

	while (lst)
	{
		ent = lst->content;
		ft_printf("%s\n", ent->name);
		lst = lst->next;
	}
}

static void		ft_ls_get_columns_width(t_list *lst, t_ls_colw *colw)
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
		if ((tmp = ft_strlen(ent->grp->gr_name)) > colw->grp)
			colw->grp = tmp;
		if ((tmp = ft_strlen(ent->pwd->pw_name)) > colw->user)
			colw->user = tmp;
		if ((tmp = ft_strlen(ent->date)) > colw->date)
			colw->date = tmp;
		if (ent->stat->st_rdev && (tmp = ft_nbrlen(minor(ent->stat->st_rdev), 10)) > colw->min)
			colw->min = tmp;
		if (ent->stat->st_rdev && (tmp = ft_nbrlen(major(ent->stat->st_rdev), 10)) > colw->maj)
			colw->maj = tmp;
		lst = lst->next;
	}
	if (colw->min > 0)
		colw->size += (colw->min + colw->maj + 1);
}

static int		ft_ls_get_block_total(t_list *lst)
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

static void		ft_ls_format_long_line(t_ls_ent *ent, t_ls_colw *colw, char *out)
{
	int i;

	i = 0;
	i += ft_sprintf(out + i, "%s ", ent->flags);
	i += ft_sprintf(out + i, "%*d ", colw->lnk + 1, ent->stat->st_nlink);
	i += ft_sprintf(out + i, "%-*s ", colw->user + 1, ent->pwd->pw_name);
	i += ft_sprintf(out + i, "%-*s ", colw->grp + 1, ent->grp->gr_name);
	if (ent->stat->st_rdev > 0)
	{
		i += ft_sprintf(out + i, "%*d, ", colw->maj, major(ent->stat->st_rdev));
		i += ft_sprintf(out + i, "%*d ", colw->min, minor(ent->stat->st_rdev));
	}
	else
		i += ft_sprintf(out + i, "%*d ", colw->size, ent->stat->st_size);
	i += ft_sprintf(out + i, "%*s ", colw->date, ent->date);
	i += ft_sprintf(out + i, "%s", ent->name);
	if (*ent->lnk)
		i += ft_sprintf(out + i, " -> %s", ent->lnk);
}

static void		ft_ls_print_files_long(t_ls *ls, t_list *lst)
{
	t_ls_ent	*ent;
	t_ls_colw	colw;
	char		line[2048];

	ft_ls_get_columns_width(lst, &colw);
	ft_printf("total %d\n", ft_ls_get_block_total(lst));
	while (lst)
	{
		ent = lst->content;
		ft_ls_format_long_line(ent, &colw, line);
		ft_printf("%s\n", line);
		lst = lst->next;
	}
}

static void		ft_ls_print_files(t_ls *ls, t_list **lst)
{
	ft_lst_mergesort(lst, ls->sortfn);
	if (FT_MASK_EQ(ls->opts, FT_LS_OPT_LONG))
		ft_ls_print_files_long(ls, *lst);
	else
		ft_ls_print_files_short(ls, *lst);
}

static void		ft_ls_print_dir(t_ls *ls, t_list **lst, int p_dirname)
{
	t_list			*tmp;
	t_ls_entries	entries;

	ft_lst_mergesort(lst, ls->sortfn);
	tmp = *lst;
	while (tmp)
	{
		if (ft_ls_get_dir_entries(ls, (char*)tmp->content, &entries))
		{
			if (p_dirname)
				ft_printf("\n%s:\n", (char*)tmp->content);
			if (entries.elst)
				ft_ls_print_err(ls, &entries.elst);
			if (entries.flst)
				ft_ls_print_files(ls, &entries.flst);
			if (FT_MASK_EQ(ls->opts, FT_LS_OPT_RECURSIVE))
			{
				if (entries.dlst)
					ft_ls_print_dir(ls, &entries.dlst, 1);
			}
			ft_ls_clean_entries(&entries);
		}
		tmp = tmp->next;
	}
}

static void		ft_ls_start(t_ls *ls, t_ls_entries *entries)
{
	int p_dirname;

	if (entries->dlst)
		p_dirname = (entries->elst || entries->flst || entries->dlst->next);
	if (entries->elst)
	{
		ls->error = 2;
		ft_ls_print_err(ls, &entries->elst);
	}
	if (entries->flst)
		ft_ls_print_files(ls, &entries->flst);
	if (entries->dlst)
		ft_ls_print_dir(ls, &entries->dlst, p_dirname);
	ft_ls_clean_entries(entries);
}

int main(int ac, char **av)
{
	t_ls			ls;
	t_ls_entries 	entries;

	ft_ls_init(&ls, &entries, ac, av);
	ft_ls_start(&ls, &entries);
	ft_ls_clean(&ls);
	return (ls.error);
}
