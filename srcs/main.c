/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:07:29 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/22 19:07:29 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_init_fstat(t_ls_file *file)
{
	if (!(file->stat = ft_memalloc(sizeof(*file->stat))))
		return ;
	if (lstat(file->filename, file->stat) == -1)
	{
		ft_memdel((void**)&file->stat);
		return ;
	}
}

void	ls_file_del(void *file_ptr, size_t size)
{
	t_ls_file *file;

	file = (t_ls_file*)file_ptr;
	if (!file)
		return ;
	ft_strdel((char**)&file->name);
	ft_strdel((char**)&file->filename);
	if (file->stat)
		ft_memdel((void**)&file->stat);
	ft_memdel((void**)&file_ptr);
}

void	ls_dir_del(void *file_ptr, size_t size)
{
	if (!file_ptr)
		return ;
	ft_memdel((void**)&file_ptr);
}

t_ls_file	*ls_file_new(char *name, const char *path)
{
	t_ls_file	*file;

	if (!(file = ft_memalloc(sizeof(*file))))
		return (NULL);
	file->name = ft_strdup(name);
	if (path)
	{
		path = ft_strjoin_free(ft_strdup(path), ft_strdup("/"));
		file->filename = ft_strjoin_free(path, ft_strdup(name));
	}
	else
		file->filename = ft_strdup(name);
	ls_init_fstat(file);
	if (file->stat)
	{
		file->pwd = getpwuid(file->stat->st_uid);
		file->grp = getgrgid(file->stat->st_gid);
	}
	return (file);
}

void	ls_list_dir(t_ls_state *state, const char *filename, t_list **flst, t_list **dlst)
{
	t_ls_file	*file;
	t_ls_file	*fdir;
	DIR			*dir;
	t_dirent	*f;

	if (!(dir = opendir(filename)))
		return ;
	while ((f = readdir(dir)))
	{
		if (!FT_MASK_EQ(state->opts, FT_LS_OPT_ALL) && *f->d_name == '.')
			continue ;
		file = ls_file_new(f->d_name, filename);
		if (file && file->stat)
		{
			ft_lstadd(flst, ft_lstnew(file, sizeof(*file)));
			if ((file->stat->st_mode & S_IFMT) == S_IFDIR &&
				!ft_strequ(file->name, ".") && !ft_strequ(file->name, ".."))
				ft_lstadd(dlst, ft_lstnew(file, sizeof(*file)));
		}
		free(file);
	}
	closedir(dir);
}

void	ls_get_files(int ac, char **av, t_list **flst, t_list **dlst, t_list **uknlst)
{
	int			i;
	t_ls_file	*file;
	t_list		*node;

	i = -1;
	while (++i < ac)
	{
		if (*av[i] == '-')
			continue ;
		file = ls_file_new(av[i], NULL);
		if (file == NULL || file->stat == NULL)
			ft_lstadd(uknlst, ft_lstnew(file, sizeof(*file)));
		else if ((file->stat->st_mode & S_IFMT) == S_IFDIR)
			ft_lstadd(dlst, ft_lstnew(file, sizeof(*file)));
		else
			ft_lstadd(flst, ft_lstnew(file, sizeof(*file)));
		free(file);
	}
	if (*flst == NULL && *dlst == NULL && *uknlst == NULL)
	{
		file = ls_file_new(".", NULL);
		ft_lstadd(dlst, ft_lstnew(file, sizeof(*file)));
		free(file);
	}
}

void	ls_print_ukn(t_list *flst)
{
	t_ls_file	*file;

	while (flst)
	{
		file = flst->content;
		ft_printf("ft_ls: %s: no such file or directory\n", file->name);
		flst = flst->next;
	}
}

int		ft_lstlen(t_list *flst)
{
	int i;

	i = 0;
	while (flst)
	{
		i++;
		flst = flst->next;
	}
	return (i);
}

int		ls_dispatch_columns(t_list *flst, int column_n, t_list *columns[])
{
	int i;
	int j;
	int lpc;

	i = -1;
	j = -1;
	lpc = ceil((double)ft_lstlen(flst) / column_n);
	while (flst)
	{
		if ((++i % lpc) == 0)
			columns[++j] = flst;
		flst = flst->next;
	}
	return (++j);
}

void	ls_print_files_short(t_ls_state *state, t_list *flst)
{
	t_ls_file *file;
	// int			i;
	// int			flst_len;
	// t_ls_file	*file;
	// int			column_width;
	// int			column_n;
	// t_list		*columns[64];

	// if (flst == NULL)
	// 	return ;
	// i = -1;
	// flst_len = ft_lstlen(flst);
	// column_width = ls_get_column_width(flst);
	// column_n = state->term_width / (column_width + 1);
	// column_n = ls_dispatch_columns(flst, column_n, columns);
	// while (++i < flst_len)
	// {
	// 	if (columns[i % column_n])
	// 	{
	// 		file = columns[i % column_n]->content;
	// 		ft_printf("%-*s ", column_width, file->name);
	// 		columns[i % column_n] = columns[i % column_n]->next;
	// 	}
	// 	if (i % column_n == column_n - 1)
	// 		ft_printf("\n");
	// }
	while (flst)
	{
		file = flst->content;
		ft_printf("%s\n", file->name);
		flst = flst->next;
	}
}

void	ls_get_all_data_width(t_list *flst, t_ls_dwith *dw)
{
	t_ls_file *file;
	int tmp;

	while (flst)
	{
		file = flst->content;
		if ((tmp = ft_nbrlen(file->stat->st_nlink, 10)) > dw->lnk)
			dw->lnk = tmp;
		if ((tmp = ft_nbrlen(file->stat->st_size, 10)) > dw->size)
			dw->size = tmp;
		if ((tmp = ft_strlen(file->grp->gr_name) + 1) > dw->grp)
			dw->grp = tmp;
		if ((tmp = ft_strlen(file->pwd->pw_name) + 1) > dw->user)
			dw->user = tmp;
		flst = flst->next;
	}
}

void	ls_print_files_long(t_ls_state *state, t_list *flst)
{
	t_ls_file *file;
	t_ls_dwith dw;

	char flags[32];

	ft_bzero(&dw, sizeof(dw));
	ls_get_all_data_width(flst, &dw);
	while (flst)
	{
		file = flst->content;
		ls_get_flags(file, flags);
		ft_printf("%s ", flags);
		ft_printf("%*d ", dw.lnk, file->stat->st_nlink);
		ft_printf("%-*s ", dw.user, file->pwd->pw_name);
		ft_printf("%-*s ", dw.grp, file->grp->gr_name);
		ft_printf("%*d ", dw.size, file->stat->st_size);
		ft_printf("%*s ", dw.date, "Feb 20 12:26");
		ft_printf("%s\n", file->name);
		flst = flst->next;
	}
}

void	ls_print_files(t_ls_state *state, t_list *flst)
{
	if (FT_MASK_EQ(state->opts, FT_LS_OPT_LONG))
		ls_print_files_long(state, flst);
	else
		ls_print_files_short(state, flst);
}


void	ls_print_dirs(t_ls_state *state, t_list *dlst, int pname)
{
	t_ls_file	*dir;
	t_list		*flst;
	t_list		*dlst2;
	t_list		**t;

	flst = NULL;
	dlst2 = NULL;
	t = &dlst;
	while (dlst)
	{
		dir = dlst->content;
		if (pname)
			ft_printf("\n%s:\n", dir->filename);
		ls_list_dir(state, dir->filename, &flst, &dlst2);
		ft_lst_mergesort(&flst, state->sortfn);
		ft_lst_mergesort(&dlst2, state->sortfn);
		ls_print_files(state, flst);
		if (FT_MASK_EQ(state->opts, FT_LS_OPT_RECURSIVE))
			ls_print_dirs(state, dlst2, 1);
		ft_lstdel(&flst, &ls_file_del);
		ft_lstdel(&dlst2, &ls_dir_del);
		dlst = dlst->next;
	}
}

int		main(int ac, char **av)
{
	t_ls_state	state;
	t_list		*flst;
	t_list		*dlst;
	t_list		*uknlst;

	flst = NULL;
	dlst = NULL;
	uknlst = NULL;
	state.exit_status = 0;
	state.term_width = ls_get_terminal_width();
	ls_init_opts(ac - 1, av + 1, &state);
	ls_get_files(ac - 1, av + 1, &flst, &dlst, &uknlst);
	ls_init_sortfn(&state);
	ft_lst_mergesort(&uknlst, &ls_alpha_sort);
	ft_lst_mergesort(&flst, state.sortfn);
	ft_lst_mergesort(&dlst, state.sortfn);
	ls_print_ukn(uknlst);
	ls_print_files(&state, flst);
	ls_print_dirs(&state, dlst, (uknlst || flst || (dlst && dlst->next != NULL)));
	ft_lstdel(&uknlst, &ls_file_del);
	ft_lstdel(&flst, &ls_file_del);
	ft_lstdel(&dlst, &ls_file_del);
	return (state.exit_status);
}
