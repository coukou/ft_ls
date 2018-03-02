/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:35:40 by orenkay           #+#    #+#             */
/*   Updated: 2018/03/01 15:57:23 by orenkay          ###   ########.fr       */
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
#include <math.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

# define FT_LS_COLOR_CHARSET	"abcdefgh"
# define FT_LS_OPT_ALL			0x01
# define FT_LS_OPT_D			0x02
# define FT_LS_OPT_F			0x04
# define FT_LS_OPT_GRP_ONLY		0x08
# define FT_LS_OPT_LONG			0x10
# define FT_LS_OPT_ONE			0x20
# define FT_LS_OPT_RECURSIVE	0x40
# define FT_LS_OPT_REVERSE		0x80
# define FT_LS_OPT_S_ATIME		0x100
# define FT_LS_OPT_S_MTIME		0x200
# define FT_LS_OPT_S_BIRTH		0x400
# define FT_LS_OPT_S_SIZE		0x800

# define FT_LS_MONTH_TIME		2629743

typedef struct winsize	t_winsize;
typedef struct dirent	t_dirent;
typedef struct group	t_group;
typedef struct passwd	t_passwd;
typedef struct stat		t_stat;

typedef struct	t_ls_entries
{
	t_list		*dlst;
	t_list		*elst;
	t_list		*flst;
}				t_ls_entries;

typedef struct	s_ls_ent
{
	const char	name[257];
	const char	*path;
	char		lnk[256];
	char		flags[32];
	char		date[256];
	char		grp_name[256];
	char		usr_name[256];
	t_stat		*stat;
}				t_ls_ent;

typedef struct 	s_ls_colw
{
	int			date;
	int			grp;
	int			lnk;
	int			maj;
	int			min;
	int			size;
	int			user;
}				t_ls_colw;

typedef struct	s_ls
{
	char		*wpath;
	int			error;
	int			opts;
	int			term_width;
	char		colors[11][32];
}				t_ls;

int				(*ft_ls_get_sortfn(t_ls *ls))(void*, void*);
int				ft_ls_sort_alpha(void *a, void *b);
t_ls_ent		*ft_ls_entnew(t_ls *ls, const char *filename);
void			ft_ls_add_entry(t_ls *ls, t_ls_ent *ent, t_ls_entries *entries, int start);
void			ft_ls_aget_entries(t_ls *ls, t_ls_entries *entries, int ac, char **av);
void			ft_ls_aget_opts(t_ls *ls, int ac, char **av);
void			ft_ls_clean(t_ls *ls);
void			ft_ls_entdel(t_ls_ent *ent);
void			ft_ls_exit(t_ls *ls, const char *msg, int exit_code);
void			ft_ls_set_color(char *color, int fc, int bc);
void			ft_ls_init_colors(t_ls *ls);
void			ft_ls_get_color(t_ls *ls, char *color, t_ls_ent *ent);
void			ft_ls_print_err(t_ls *ls, t_list **lst);
void			ft_ls_print_files_short(t_ls *ls, t_list *lst);
void			ft_ls_print_files_long(t_ls *ls, t_list *lst);
void			ft_ls_print_dir(t_ls *ls, t_list **lst, int print_path);
void			ft_ls_format_long_line(t_ls_ent *ent, t_ls_colw *colw, char *color, char *out);
void			ft_ls_get_columns_width(t_list *lst, t_ls_colw *colw);
int				ft_ls_get_max_column_width(t_list *lst);
int				ft_ls_get_block_total(t_list *lst);
void			ft_ls_set_path(t_ls *ls, const char *path);
int				ft_ls_sort_birth(void *a, void *b);
void			ft_ls_sort_entries(t_ls *ls, t_ls_entries *entries);
int				ft_ls_get_dir_entries(t_ls *ls, const char *path, t_ls_entries *entries);
void			ft_ls_print_files(t_ls *ls, t_list **lst);
char			*ft_ls_get_ent_error(t_ls_ent *ent);
void			ft_ls_entdel(t_ls_ent *ent);
void			ft_ls_add_err_entry(t_ls_ent *ent, t_ls_entries *entries);
void			ft_ls_add_entry(t_ls *ls, t_ls_ent *ent, t_ls_entries *entries, int start);
void			ft_ls_set_date(t_ls *ls, t_ls_ent *ent);
int				ft_ls_get_dir_entries(t_ls *ls, const char *path, t_ls_entries *entries);

#endif
