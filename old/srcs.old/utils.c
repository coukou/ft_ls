/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:33:18 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/22 16:53:11 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_get_file_letter(t_ls_file *file)
{
	int type;

	type = file->stat->st_mode & S_IFMT;
	if (type == S_IFSOCK)
		return ('s');
	else if (type == S_IFLNK)
		return ('l');
	else if (type == S_IFBLK)
		return ('b');
	else if (type == S_IFDIR)
		return ('d');
	else if (type == S_IFCHR)
		return ('c');
	else if (type == S_IFIFO)
		return ('p');
	else
		return ('-');
}

int		ls_get_column_width(t_list *flst)
{
	int width;
	int tmp;

	width = 0;
	while (flst)
	{
		tmp = ft_strlen(((t_ls_file*)flst->content)->name);
		if (tmp > width)
			width = tmp;
		flst = flst->next;
	}
	return (width);
}

int		ls_get_terminal_width()
{
	struct winsize	w;
	if (ioctl(0, TIOCGWINSZ, &w) == -1)
		return (0);
	return (w.ws_col);
}

void	ls_get_flags(t_ls_file *file, char out[])
{
	out[0] = ls_get_file_letter(file);
	out[1] = (FT_MASK_EQ(file->stat->st_mode, S_IRUSR) ? 'r' : '-');
	out[2] = (FT_MASK_EQ(file->stat->st_mode, S_IWUSR) ? 'w' : '-');
	out[3] = (FT_MASK_EQ(file->stat->st_mode, S_IXUSR) ? 'x' : '-');
	out[4] = (FT_MASK_EQ(file->stat->st_mode, S_IRGRP) ? 'r' : '-');
	out[5] = (FT_MASK_EQ(file->stat->st_mode, S_IWGRP) ? 'w' : '-');
	out[6] = (FT_MASK_EQ(file->stat->st_mode, S_IXGRP) ? 'x' : '-');
	out[7] = (FT_MASK_EQ(file->stat->st_mode, S_IROTH) ? 'r' : '-');
	out[8] = (FT_MASK_EQ(file->stat->st_mode, S_IWOTH) ? 'w' : '-');
	out[9] = (FT_MASK_EQ(file->stat->st_mode, S_IXOTH) ? 'x' : '-');
	out[10] = ' ';
	out[11] = 0;
}

void	ls_print_usage_exit()
{
	ft_printf("usage: [-%s] [file ...]\n", "Ralrt");
	exit(1);
}
