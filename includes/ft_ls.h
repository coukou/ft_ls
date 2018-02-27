/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:35:40 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/26 20:31:55 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

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

typedef struct	t_ls_entries
{
	t_list		*elst;
	t_list		*flst;
	t_list		*dlst;
}				t_ls_entries;

typedef struct	s_ls_ent
{
	const char	name[256];
	const char	*path;
	char		lnk[256];
	char		flags[32];
	char		date[256];
	t_stat		*stat;
	t_passwd	*pwd;
	t_group 	*grp;
}				t_ls_ent;

typedef struct 	s_ls_colw
{
	int			lnk;
	int			size;
	int			grp;
	int			user;
	int			date;
}				t_ls_colw;

typedef struct	s_ls
{
	int			opts;
	int			error;
	int			(*sortfn)(void*, void*);
	char		*wpath;
	int			term_width;
}				t_ls;

void			ft_ls_path_push(t_ls *ls, const char *path);
void			ft_ls_path_pop(t_ls *ls);
void			ft_ls_exit(t_ls *ls, const char *msg);
void			ft_ls_clean(t_ls *ls);
void			ft_ls_aget_opts(t_ls *ls, int ac, char **av);
void			ft_ls_aget_entries(t_ls *ls, t_ls_entries *entries, int ac, char **av);
int				ft_ls_get_sortfn(t_ls *ls);
void			ft_ls_clean_entries(t_ls_entries *entries);
void			ft_ls_entdel(t_ls_ent *ent);
void			ft_ls_add_entry(t_ls_ent *ent, t_ls_entries *entries, int start);
void			ft_ls_clean_entries(t_ls_entries *entries);
t_ls_ent		*ft_ls_entnew(t_ls *ls, const char *filename);
void			ft_ls_init_sortfn(t_ls *ls);
int				ft_ls_sort_alpha(void *a, void *b);

#endif
