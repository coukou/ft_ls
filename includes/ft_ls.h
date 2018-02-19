/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:19:25 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/19 20:27:00 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

#include "libft/list.h"
#include "ft_printf.h"

# define M_OPT_LONG			0x01
# define M_OPT_RECURSIVE	0x02
# define M_OPT_ALL			0x04
# define M_OPT_REVERSE		0x08
# define M_OPT_STIME		0x10

typedef struct	stat		t_stat;
typedef struct	dirent	t_dirent;

typedef struct	s_ls_file
{
	const char	*name;
	t_stat		*stat;
}				t_ls_file;

typedef struct	s_ls_state
{
	int			opts;
	int			exit_status;
	t_list		*files;
}				t_ls_state;

#endif
