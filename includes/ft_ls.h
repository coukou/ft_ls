/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:19:25 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/20 15:50:26 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include <sys/ioctl.h>
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
# define M_OPT_S_MTIME		0x10

typedef struct	stat	t_stat;
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
	int			(*sort_fn)(void*, void*);
	size_t		term_width;
	size_t		term_height;
}				t_ls_state;

void	ls_print_dirs(t_ls_state *state, t_list *dirs, char *apath);

#endif
