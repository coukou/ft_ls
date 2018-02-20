/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:07:29 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/20 12:05:27 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}

int		ls_get_option(int c)
{
	if (c == 'a')
		return (M_OPT_ALL);
	else if (c == 'R')
		return (M_OPT_RECURSIVE);
	else if (c == 'r')
		return (M_OPT_REVERSE);
	else if (c == 'l')
		return (M_OPT_LONG);
	else if (c == 't')
		return (M_OPT_S_MTIME);
	else return (0);
}

void	ls_print_usage_exit()
{
	ft_printf("usage: [-%s] [file ...]\n", "Ralrt");
	exit(1);
}

void	ls_parse_opts(char *opts, t_ls_state *state)
{
	int	i;
	int opt;

	i = -1;
	while (opts[++i])
	{
		if ((opt = ls_get_option(opts[i])))
			state->opts |= opt;
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n", opts[i]);
			ls_print_usage_exit();
		}
	}
}

void	ls_add_file(const char *filename, const char *dir, t_list **lst)
{
	t_ls_file	*file;
	t_list		*node;
	char		*apath;

	if (!(file = ft_memalloc(sizeof(*file))))
		return ;
	file->name = filename;
	file->stat = ft_memalloc(sizeof(*file->stat));
	if (!file->stat)
	{
		ft_memdel((void**)&file);
		return ;
	}
	apath = (dir) ? ft_strjoin(dir, filename) : (char*)filename;
	lstat(apath, file->stat);
	node = ft_lstnew(file, sizeof(*file));
	ft_memdel((void**)&file);
	ft_lstadd(lst, node);
	if (dir)
		ft_strdel(&apath);
}

void	ls_parse_args(int ac, char **av, t_ls_state *state)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		if (*(av[i]) == '-')
			ls_parse_opts(av[i] + 1, state);
		else
			ls_add_file(av[i], NULL, &state->files);
	}
	if (state->files == NULL)
		ls_add_file(".", NULL, &state->files);
}

void	ls_print_not_found(t_ls_state *state)
{
	t_list *lst;
	t_ls_file *file;

	lst = state->files;
	while (lst)
	{
		file = (t_ls_file*)lst->content;
		if (file->stat->st_mode == 0)
			ft_printf("ft_ls: %s: No such file or directory\n", file->name);
		lst = lst->next;
	}
}

int		ls_alpha_sort(void *a, void *b)
{
	return (ls_strcmp(((t_ls_file*)a)->name, ((t_ls_file*)b)->name));
}

int		ls_alpha_sort_rev(void *a, void *b)
{
	return (ls_alpha_sort(b, a));
}

int		ls_mtime_sort(void *a, void *b)
{
	time_t atime;
	time_t btime;

	atime = ((t_ls_file*)a)->stat->st_mtime;
	btime = ((t_ls_file*)b)->stat->st_mtime;
	if (atime == btime)
		return (ls_alpha_sort(a, b));
	return (atime > btime) ? -1 : 1;
}

int		ls_mtime_sort_rev(void *a, void *b)
{
	return (ls_mtime_sort(b, a));
}

void	ls_print_files_line(t_ls_state *state, t_list *files)
{
	t_ls_file *file;

	while (files)
	{
		file = (t_ls_file*)files->content;
		ft_printf("%s %d %s %s %d %s %d %.2d:%.2d %s\n", "----------", 0, "user", "user", 4096, "Month", 20, 0, 0, file->name);
		files = files->next;
	}
}

int		ft_lstlen(t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ls_print_files_column(t_ls_state *state, t_list *files)
{
	while (files)
	{
		ft_printf("%-*s  ", 0, ((t_ls_file*)files->content)->name);
		files = files->next;
	}
	ft_printf("\n");
}

void	ls_print_files(t_ls_state *state, t_list *files)
{
	if (FT_MASK_EQ(state->opts, M_OPT_LONG))
		ls_print_files_line(state, files);
	else
		ls_print_files_column(state, files);
}

void	ls_print_dirs(t_ls_state *state, t_list *dirs, char *apath);

void	ls_filedel(void *content, size_t size)
{
	t_ls_file *file;

	file = (t_ls_file*)content;
	ft_memdel((void**)&file->stat);
	ft_memdel((void**)&file);
}

void	ls_print_dir(t_ls_state *state, t_ls_file *dir, char *apath, int print_dir)
{
	DIR			*dd;
	t_dirent	*dent;
	t_list		*files;

	files = NULL;
	dd = opendir(apath);
	if (print_dir)
		ft_printf("\n%.*s:\n", ft_strlen(apath) - 1, apath);
	while (dd && (dent = readdir(dd)))
	{
		if (!(FT_MASK_EQ(state->opts, M_OPT_ALL)) && *dent->d_name == '.')
			continue ;
		ls_add_file(dent->d_name, apath, &files);
	}
	ft_lst_mergesort(&files, state->sort_fn);
	ls_print_files(state, files);
	if ((FT_MASK_EQ(state->opts, M_OPT_RECURSIVE)))
		ls_print_dirs(state, files, apath);
	ft_strdel(&apath);
	ft_lstdel(&files, &ls_filedel);
	if (dd)
		closedir(dd);
}

void	ls_print_dirs(t_ls_state *state, t_list *files, char *apath)
{
	char		*path;
	t_ls_file	*file;

	while (files)
	{
		file = ((t_ls_file*)files->content);
		if ((file->stat->st_mode & S_IFMT) != S_IFDIR ||
			ft_strequ(file->name, ".") ||
			ft_strequ(file->name, ".."))
		{
			files = files->next;
			continue ;
		}
		path = ft_strjoin(file->name, "/");
		ls_print_dir(state, file, ft_strjoin_free(ft_strdup(apath), path), 1);
		files = files->next;
	}
}

void	ls_print(t_ls_state *state)
{
	t_list *lst;
	t_ls_file *file;

	lst = state->files;
	while (lst)
	{
		file = (t_ls_file*)lst->content;
		if ((file->stat->st_mode & S_IFMT) == S_IFDIR)
			ls_print_dir(state, file, ft_strjoin(file->name, "/"), state->files->next != NULL);
		else if ((file->stat->st_mode & S_IFMT) != 0)
			ft_printf("%s\n", file->name);
		lst = lst->next;
	}
}

int		ls_1st_sort(void *a, void *b)
{
	t_ls_file *af;
	t_ls_file *bf;

	af = (t_ls_file*)a;
	bf = (t_ls_file*)b;
	if ((af->stat->st_mode & S_IFMT) == S_IFDIR &&
		(bf->stat->st_mode & S_IFMT) != S_IFDIR)
		return (1);
	if ((af->stat->st_mode & S_IFMT) != S_IFDIR &&
		(bf->stat->st_mode & S_IFMT) == S_IFDIR)
		return (-1);
	return (ft_strcmp(af->name, bf->name));
}

void	ls_init_sortfn(t_ls_state *state)
{
	int reverse;

	reverse = FT_MASK_EQ(state->opts, M_OPT_REVERSE);
	if (FT_MASK_EQ(state->opts, M_OPT_S_MTIME))
		state->sort_fn = (!reverse) ? &ls_mtime_sort : &ls_mtime_sort_rev;
	else
		state->sort_fn = (!reverse) ? &ls_alpha_sort : &ls_alpha_sort_rev;
}

int		main(int ac, char **av)
{
	struct winsize w;
	t_ls_state	state;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	state.exit_status = 0;
	state.files = NULL;
	state.term_width = w.ws_col;
	ls_parse_args(ac - 1, av + 1, &state);
	ls_init_sortfn(&state);
	ft_lst_mergesort(&state.files, &ls_1st_sort);
	ls_print_not_found(&state);
	ls_print(&state);
	ft_lstdel(&state.files, &ls_filedel);
	return (state.exit_status);
}
