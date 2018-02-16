/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:07:29 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/16 20:38:45 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		return (M_OPT_STIME);
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
			ft_printf("ls: illegal option -- %c\n", opts[i]);
			ls_print_usage_exit();
		}
	}
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
}

t_ls_file	*ls_new_file(const char *filename)
{
	t_stat		s;
	t_ls_file	*file;

	ft_bzero(&s, sizeof(s));
	stat(filename, &s);
	file = ft_memalloc(sizeof(*file));
	if (file == NULL)
		return (NULL);
	file->name = filename;
	file->stat = s;
	return (file);
}

void	ls_parse_args(int ac, char **av, t_ls_state *state)
{
	t_ls_file	*file;
	int			i;

	i = -1;
	while (++i < ac)
	{
		if (*(av[i]) == '-')
			ls_parse_opts(av[i] + 1, state);
		else
		{
			file = ls_new_file(av[i]);
			if ((file->stat.st_mode & S_IFMT) == 0)
				ft_lstadd(&state->files_nf, ft_lstnew(file, sizeof(*file)));
			else if ((file->stat.st_mode & S_IFMT) == S_IFDIR)
			{
				ft_printf("je suis un dossier %s\n", file->name);
				free(file);
				// create dir and add to &state->dir
			}
			else
				ft_lstadd(&state->files, ft_lstnew(file, sizeof(*file)));
		}
	}
	if (state->files == NULL && state->files_nf == NULL && state->dirs == NULL)
		ft_printf("pas de fichiers / dossiers reçu en arguments :(\n");
}

int		ls_sort_files(void *a, void *b)
{
	return (ft_strcmp(((t_ls_file*)a)->name, ((t_ls_file*)b)->name));
}

void	ls_print_files(t_ls_state *state)
{
	t_list *tmp;

	ft_lst_mergesort(&state->files, &ls_sort_files);
	tmp = state->files;
	while (tmp)
	{
		ft_printf("%s\n", ((t_ls_file*)tmp->content)->name);
		tmp = tmp->next;
	}
}

void	ls_print_files_nf(t_ls_state *state)
{
	t_list *tmp;

	ft_lst_mergesort(&state->files_nf, &ls_sort_files);
	tmp = state->files_nf;
	if (tmp)
		state->exit_status = 1;
	while (tmp)
	{
		ft_printf("ls: %s: No such file or directory\n", ((t_ls_file*)tmp->content)->name);
		tmp = tmp->next;
	}
}

int		main(int ac, char **av)
{
	t_ls_state	state;

	state.exit_status = 0;
	ls_parse_args(ac - 1, av + 1, &state);
	ls_print_files_nf(&state);
	ls_print_files(&state);
	return (state.exit_status);
}
