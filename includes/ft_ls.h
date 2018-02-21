/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:19:25 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/21 21:29:24 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#include "libft/list.h"
#include "ft_printf.h"

# define FT_LS_OPT_LONG			0x01
# define FT_LS_OPT_RECURSIVE	0x02
# define FT_LS_OPT_ALL			0x04
# define FT_LS_OPT_REVERSE		0x08
# define FT_LS_OPT_S_MTIME		0x10

typedef struct	stat	t_stat;
typedef struct	dirent	t_dirent;
typedef struct	group	t_group;
typedef struct	passwd	t_passwd;

typedef struct	s_ls_file
{
	char		*name;
	char		*filename;
	t_stat		*stat;
	t_passwd	*pwd;
	t_group 	*grp;
}				t_ls_file;

typedef struct	s_ls_state
{
	int			opts;
	int			exit_status;
	int			(*sortfn)(void*, void*);
}				t_ls_state;

// SORT
// ----------------

int		ls_alpha_sort(void *a, void *b);
void	ls_init_sortfn(t_ls_state *state);

// UTILS
// ----------------

void	ls_print_usage_exit();

// OPTIONS
// ----------------

void	ls_init_opts(int ac, char **av, t_ls_state *state);

#endif
