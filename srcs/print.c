/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:36:37 by spopieul          #+#    #+#             */
/*   Updated: 2018/03/03 17:45:39 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_print_err(t_ls *ls, t_list **lst)
{
	char	*err;

	(void)ls;
	while ((err = ft_lstpop(lst)))
	{
		ft_printf("ft_ls: %s\n", err);
		ft_strdel(&err);
	}
}

void		ft_ls_print_files_short(t_ls *ls, t_list *lst)
{
	t_ls_ent	*ent;
	char		color[12];

	while ((ent = ft_lstpop(&lst)))
	{
		if (FT_MASK_EQ(ls->opts, FT_LS_OPT_COLOR))
		{
			ft_ls_get_color(ls, color, ent);
			ft_printf("%s%s\033[0m\n", color, ent->name);
		}
		else
			ft_printf("%s\n", ent->name);
		ft_ls_entdel(ent);
	}
}

void		ft_ls_print_files_long(t_ls *ls, t_list *lst)
{
	t_ls_ent	*ent;
	t_ls_colw	colw;
	char		line[4096];
	char		color[12];

	ft_ls_get_columns_width(lst, &colw);
	while ((ent = ft_lstpop(&lst)))
	{
		*color = 0;
		if (FT_MASK_EQ(ls->opts, FT_LS_OPT_COLOR))
			ft_ls_get_color(ls, color, ent);
		ft_ls_format_long_line(ent, &colw, color, line);
		ft_printf("%s\n", line);
		ft_ls_entdel(ent);
	}
}

void		ft_ls_print_files(t_ls *ls, t_list **lst)
{
	if (FT_MASK_EQ(ls->opts, FT_LS_OPT_LONG))
		ft_ls_print_files_long(ls, *lst);
	else
		ft_ls_print_files_short(ls, *lst);
}

void		ft_ls_print_dir(t_ls *ls, t_list **lst, int print_path)
{
	t_ls_ent		*ent;
	t_ls_entries	entries;

	while ((ent = ft_lstpop(lst)))
	{
		entries.elst = NULL;
		entries.flst = NULL;
		entries.dlst = NULL;
		if (ft_ls_get_dir_entries(ls, ent->path, &entries))
		{
			if (print_path)
				ft_printf("\n%s:\n", ent->path);
			if (FT_MASK_EQ(ls->opts, FT_LS_OPT_LONG))
				ft_printf("total %d\n", ft_ls_get_block_total(entries.flst));
			ft_ls_print_err(ls, &entries.elst);
			ft_ls_print_files(ls, &entries.flst);
			ft_ls_print_dir(ls, &entries.dlst, 1);
		}
		ft_ls_entdel(ent);
	}
}
