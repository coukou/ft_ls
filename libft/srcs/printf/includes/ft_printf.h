/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:46:39 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/25 17:52:58 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>
# include "libft.h"

# define PRINTF_BUFF_SIZE 64

# define M_FLAG_MINUS	0x01
# define M_FLAG_PLUS	0x02
# define M_FLAG_SPACE	0x04
# define M_FLAG_HASH	0x08
# define M_FLAG_ZERO	0x10

# define M_LENGTH_H		0x01
# define M_LENGTH_HH	0x02
# define M_LENGTH_L		0x04
# define M_LENGTH_LL	0x08
# define M_LENGTH_J		0x10
# define M_LENGTH_Z		0x20
# define M_LENGTH_T		0x40
# define M_LENGTH_L_	0x80

typedef struct	s_pf_data
{
	char			value[65];
	size_t			len;
	char			*sign;
	char			*bpad;
	size_t			width;
	size_t			precision;
	char			*pchar;
}				t_pf_data;

typedef struct	s_pf_buffer
{
	unsigned char	*data;
	size_t			offset;
	size_t			capacity;
	size_t			writed;
}				t_pf_buffer;

typedef struct	s_pf_state
{
	int				specifier;
	int				flags;
	int				precision;
	int				width;
	int				length;
	va_list			args;
	t_pf_buffer		*pbuff;
	const char		**fmt;
}				t_pf_state;

int				ft_pf_write_hexcolor(t_pf_state *state, char *color, int type);
void			ft_pf_extract_color
	(t_pf_state *state, const char **fmt, char color[], int max);
void			ft_pf_write_color_reset(t_pf_state *state, int type);
int				ft_printf(const char *fmt, ...);
void			ft_pf_buffer_flush(t_pf_buffer *buffer);
void			ft_pf_buffer_write_n
	(t_pf_buffer *buffer, char *data, size_t size);
void			ft_pf_buffer_write(t_pf_buffer *buffer, char *data);
void			ft_pf_get_signed(t_pf_state *state, char out[]);
void			ft_pf_get_unsigned(t_pf_state *state, char out[]);
void			ft_pf_format_wc(t_pf_state *state);
void			ft_pf_format_c(t_pf_state *state);
void			ft_pf_format_unknown(t_pf_state *state);
void			ft_pf_format_p(t_pf_state *state);
void			ft_pf_format_ws(t_pf_state *state);
void			ft_pf_format_s(t_pf_state *state);
void			ft_pf_format_signed(t_pf_state *state);
void			ft_pf_format_unsigned(t_pf_state *state);
void			ft_pf_format_n(t_pf_state *state);
int				ft_pf_get_width(t_pf_state *state);
int				ft_pf_get_precision(t_pf_state *state);
int				ft_pf_get_length(t_pf_state *state);
int				ft_pf_get_flags(t_pf_state *state);
int				ft_pf_atoi(const char **fmt);
size_t			ft_pf_get_pad_width(t_pf_state *state, t_pf_data *data);
int				ft_pf_get_base(t_pf_state *state);
char			*ft_pf_extract_sign(t_pf_state *state, char data[]);
char			*ft_pf_get_base_padding(t_pf_state *state, t_pf_data *data);
void			ft_pf_write_padding(t_pf_state *state, int width, char *pchar);
void			ft_pf_write_data(t_pf_state *state, t_pf_data *data);
void			ft_pf_write_ws
	(t_pf_state *state, t_pf_data *data, wchar_t *wstr);
void			ft_pf_write_s(t_pf_state *state, t_pf_data *data, char *str);
#endif
