/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 21:12:30 by spopieul          #+#    #+#             */
/*   Updated: 2018/03/01 15:54:43 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_get_columns(t_ls *ls, t_list *lst)
{
	int column_width;

	column_width = ft_ls_get_column_width(lst);
	return ceil((double)ls->term_width / column_width);
}
