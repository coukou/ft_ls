/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:54:24 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/25 18:07:10 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

static void		ft_pf_format_dispatch(int c, t_pf_state *state)
{
	if (state->specifier == 'S')
		ft_pf_format_ws(state);
	else if (state->specifier == 'C')
		ft_pf_format_wc(state);
	else if (c == 's')
		ft_pf_format_s(state);
	else if (c == 'c')
		ft_pf_format_c(state);
	else if (c == 'p')
		ft_pf_format_p(state);
	else if (c == 'd' || c == 'i')
		ft_pf_format_signed(state);
	else if (c == 'u' || c == 'o' || c == 'x' || c == 'b')
		ft_pf_format_unsigned(state);
	else if (c == 'n')
		ft_pf_format_n(state);
	else
		ft_pf_format_unknown(state);
	(*state->fmt)++;
}

static void		ft_pf_format(t_pf_state *state)
{
	int rsum;

	rsum = 1;
	state->flags = 0;
	state->precision = -1;
	state->width = -1;
	state->length = 0;
	while (rsum)
	{
		rsum = 0;
		rsum += ft_pf_get_flags(state);
		rsum += ft_pf_get_width(state);
		rsum += ft_pf_get_precision(state);
		rsum += ft_pf_get_length(state);
	}
	if (**state->fmt == 0)
		return ;
	state->specifier = **state->fmt;
	ft_pf_format_dispatch(ft_tolower(**state->fmt), state);
}

static void		ft_pf_format_color(t_pf_state *state)
{
	char		color[64];
	int			type;
	const char	*tmp;

	tmp = *state->fmt;
	ft_pf_extract_color(state, &tmp, color, 64);
	ft_strtolower(color);
	type = 0;
	if (*color == '_')
		type = 1;
	else if (*color == '@')
		type = 2;
	if (type != 0)
		ft_strcpy(color, color + 1);
	if (*color == 'r' || ft_strcmp("reset", color) == 0)
	{
		ft_pf_write_color_reset(state, type);
		*state->fmt = tmp;
	}
	else if (*color == '#' && ft_pf_write_hexcolor(state, color + 1, type))
		*state->fmt = tmp;
	else
		ft_pf_buffer_write_n(state->pbuff, (char*)*state->fmt - 1, 1);
}

int				ft_sprintf(char *out, const char *fmt, ...)
{
	t_pf_state	state;
	t_pf_buffer	pbuff;

	pbuff.data = (unsigned char*)out;
	pbuff.capacity = 0;
	pbuff.writed = 0;
	pbuff.offset = 0;
	state.pbuff = &pbuff;
	state.fmt = &fmt;
	va_start(state.args, fmt);
	while (*fmt)
	{
		if (*fmt == '%' && *(++fmt))
			ft_pf_format(&state);
		else if (*fmt == '{' && *(++fmt))
			ft_pf_format_color(&state);
		else if (*fmt)
			ft_pf_buffer_write_n(&pbuff, (char*)fmt++, 1);
	}
	va_end(state.args);
	out[pbuff.writed] = 0;
	return (pbuff.writed);
}

int				ft_printf(const char *fmt, ...)
{
	t_pf_state	state;
	t_pf_buffer	pbuff;
	char		buff[PRINTF_BUFF_SIZE];

	pbuff.data = (unsigned char*)buff;
	pbuff.capacity = PRINTF_BUFF_SIZE;
	pbuff.writed = 0;
	pbuff.offset = 0;
	state.pbuff = &pbuff;
	state.fmt = &fmt;
	va_start(state.args, fmt);
	while (*fmt)
	{
		if (*fmt == '%' && *(++fmt))
			ft_pf_format(&state);
		else if (*fmt == '{' && *(++fmt))
			ft_pf_format_color(&state);
		else if (*fmt)
			ft_pf_buffer_write_n(&pbuff, (char*)fmt++, 1);
	}
	va_end(state.args);
	ft_pf_buffer_flush(&pbuff);
	return (pbuff.writed);
}
