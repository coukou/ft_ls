/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:19:25 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/24 02:19:33 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS


#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <errno.h>


#include "libft/list.h"
#include "ft_printf.h"

# define FT_LS_OPT_LONG			0x01
# define FT_LS_OPT_RECURSIVE	0x02
# define FT_LS_OPT_ALL			0x04
# define FT_LS_OPT_REVERSE		0x08
# define FT_LS_OPT_S_MTIME		0x10
# define FT_LS_OPT_ONE			0x20

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
	char		date[32];
	char		lnk[1024];
}				t_ls_file;

typedef struct	s_ls_dwidth
{
	int lnk;
	int user;
	int grp;
	int size;
	int date;
}				t_ls_dwith;

typedef struct	s_ls_dir
{
	char		*path;
	t_list		*ulst;
	t_list		*flst;
	t_list		*dlst;
}				t_ls_dir;

typedef struct	s_ls_state
{
	int			opts;
	int			exit_status;
	int			(*sortfn)(void*, void*);
	int			term_width;
}				t_ls_state;

// SORT
// ----------------

int		ls_alpha_sort(void *a, void *b);
void	ls_init_sortfn(t_ls_state *state);

// UTILS
// ----------------

void	ls_print_usage_exit();
int		ls_get_terminal_width();
void	ls_get_flags(t_ls_file *file, char out[]);
int		ls_get_column_width(t_list *flst);
int		ls_get_lines_per_column(t_ls_state *state, t_list *flst, int column_width);

// OPTIONS
// ----------------

void	ls_init_opts(int ac, char **av, t_ls_state *state);

#endif
