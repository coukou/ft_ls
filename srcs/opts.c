/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:44:22 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/21 17:34:21 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ls_get_opt_flag(int c)
{
	if (c == 'a')
		return (FT_LS_OPT_ALL);
	else if (c == 'R')
		return (FT_LS_OPT_RECURSIVE);
	else if (c == 'r')
		return (FT_LS_OPT_REVERSE);
	else if (c == 'l')
		return (FT_LS_OPT_LONG);
	else if (c == 't')
		return (FT_LS_OPT_S_MTIME);
	else
		return (0);
}

void			ls_init_opts(int ac, char **av, t_ls_state *state)
{
	int	i;
	int opt;

	i = -1;
	while (++i < ac)
	{
		if (*(av[i]) == '-')
		{
			if ((opt = ls_get_opt_flag(av[i][1])))
				state->opts |= opt;
			else
			{
				ft_printf("ft_ls: illegal option -- %c\n", av[i][1]);
				ls_print_usage_exit();
			}
		}
	}
}
