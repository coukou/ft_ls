/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:33:11 by spopieul          #+#    #+#             */
/*   Updated: 2018/03/08 20:16:28 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_ls_set_color(char *color, int fc, int bc)
{
	int i;
	int fg;
	int bg;

	fg = ft_strfind(FT_LS_COLOR_CHARSET, ft_tolower(fc));
	bg = ft_strfind(FT_LS_COLOR_CHARSET, ft_tolower(bc));
	i = 0;
	if (ft_isupper(fc))
		i += ft_sprintf(color + i, ";1");
	if (fg > -1)
		i += ft_sprintf(color + i, ";%d", 30 + fg);
	if (bg > -1)
		i += ft_sprintf(color + i, ";%d", 40 + bg);
	if (i == 0)
		*color = 0;
}

void		ft_ls_init_colors(t_ls *ls)
{
	int		i;
	char	*env_colors;
	int		fc;
	int		bc;

	i = -1;
	env_colors = getenv("LSCOLORS");
	while (++i < 11)
	{
		if (*env_colors)
		{
			if ((fc = *(env_colors++)) == 0)
				continue ;
			if ((bc = *(env_colors++)) == 0)
				continue ;
			ft_ls_set_color(ls->colors[i], fc, bc);
		}
		else
			ls->colors[i][0] = 0;
	}
}

void		ft_ls_get_color_dir(t_ls *ls, char *color, t_ls_ent *ent)
{
	if ((FT_MASK_EQ(ent->stat->st_mode, S_IWOTH)) &&
		(FT_MASK_EQ(ent->stat->st_mode, S_ISVTX)))
		ft_sprintf(color, "\033[%sm", ls->colors[9]);
	else if ((FT_MASK_EQ(ent->stat->st_mode, S_IWOTH)))
		ft_sprintf(color, "\033[%sm", ls->colors[10]);
	else
		ft_sprintf(color, "\033[%sm", ls->colors[0]);
}

void		ft_ls_get_color_exe(t_ls *ls, char *color, t_ls_ent *ent)
{
	if ((FT_MASK_EQ(ent->stat->st_mode, S_ISUID)))
		ft_sprintf(color, "\033[%sm", ls->colors[7]);
	else if ((FT_MASK_EQ(ent->stat->st_mode, S_ISGID)))
		ft_sprintf(color, "\033[%sm", ls->colors[8]);
	else
		ft_sprintf(color, "\033[%sm", ls->colors[4]);
}

void		ft_ls_get_color(t_ls *ls, char *color, t_ls_ent *ent)
{
	if ((ent->stat->st_mode & S_IFMT) == S_IFDIR)
		ft_ls_get_color_dir(ls, color, ent);
	else if ((ent->stat->st_mode & S_IFMT) == S_IFLNK)
		ft_sprintf(color, "\033[%sm", ls->colors[1]);
	else if ((ent->stat->st_mode & S_IFMT) == S_IFSOCK)
		ft_sprintf(color, "\033[%sm", ls->colors[2]);
	else if ((ent->stat->st_mode & S_IFMT) == S_IFIFO)
		ft_sprintf(color, "\033[%sm", ls->colors[3]);
	else if ((FT_MASK_EQ(ent->stat->st_mode, S_IEXEC)))
		ft_ls_get_color_exe(ls, color, ent);
	else if ((ent->stat->st_mode & S_IFMT) == S_IFBLK)
		ft_sprintf(color, "\033[%sm", ls->colors[5]);
	else if ((ent->stat->st_mode & S_IFMT) == S_IFCHR)
		ft_sprintf(color, "\033[%sm", ls->colors[6]);
	else
		*color = 0;
}
