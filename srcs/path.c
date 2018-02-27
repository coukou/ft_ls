/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:25:47 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/26 14:35:03 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_path_push(t_ls *ls, const char *path)
{
	char	*tmp;
	size_t	size;

	size = ft_strlen(ls->wpath);
	size += ft_strlen(path);
	tmp = ft_strnew(size + 1);
	ft_sprintf(tmp, "%s%s/", ls->wpath, path);
	ft_strdel(&ls->wpath);
	ls->wpath = tmp;
}

void	ft_ls_path_pop(t_ls *ls)
{
	size_t offset;

	if ((offset = ft_strlen(ls->wpath)) > 0)
	{
		offset--;
		while (--offset)
		{
			if (ls->wpath[offset] == '/')
			{
				ls->wpath[offset + 1] = 0;
				return ;
			}
		}
		*(ls->wpath) = 0;
	}
}
