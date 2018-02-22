/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:44:22 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/22 18:51:05 by spopieul         ###   ########.fr       */
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
	int j;
	int opt;

	i = -1;
	while (++i < ac)
	{
		j = -1;
		if (av[i][++j] == '-')
		{
			while (av[i][++j] && !ft_isspace(av[i][j]))
			{
				if ((opt = ls_get_opt_flag(av[i][j])) > 0)
					state->opts |= opt;
				else
				{
					// ft_printf("ft_ls: illegal option -- %c\n", av[i][1]);
					// ls_print_usage_exit();
				}
			}
		}
	}
}
