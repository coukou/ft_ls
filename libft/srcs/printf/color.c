/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 18:47:18 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/25 17:56:11 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

static void	ft_pf_write_hex6(t_pf_state *state, int value)
{
	char	tmp[4];

	ft_lltoa((value >> 16) & 0xFF, 10, tmp);
	ft_pf_buffer_write(state->pbuff, tmp);
	ft_pf_buffer_write_n(state->pbuff, ";", 1);
	ft_lltoa((value >> 8) & 0xFF, 10, tmp);
	ft_pf_buffer_write(state->pbuff, tmp);
	ft_pf_buffer_write_n(state->pbuff, ";", 1);
	ft_lltoa(value & 0xFF, 10, tmp);
	ft_pf_buffer_write(state->pbuff, tmp);
	ft_pf_buffer_write_n(state->pbuff, "m", 1);
}

static void	ft_pf_write_hex3(t_pf_state *state, int value)
{
	char	tmp[4];

	ft_lltoa(((value >> 8) & 0xF) * 17, 10, tmp);
	ft_pf_buffer_write(state->pbuff, tmp);
	ft_pf_buffer_write_n(state->pbuff, ";", 1);
	ft_lltoa(((value >> 4) & 0xF) * 17, 10, tmp);
	ft_pf_buffer_write(state->pbuff, tmp);
	ft_pf_buffer_write_n(state->pbuff, ";", 1);
	ft_lltoa((value & 0xF) * 17, 10, tmp);
	ft_pf_buffer_write(state->pbuff, tmp);
	ft_pf_buffer_write_n(state->pbuff, "m", 1);
}

int			ft_pf_write_hexcolor(t_pf_state *state, char *color, int type)
{
	size_t	hexlen;
	int		value;
	int		start;

	start = state->pbuff->writed;
	hexlen = ft_strlen(color);
	if (hexlen != 6 && hexlen != 3)
		return (0);
	value = (int)ft_atoll(color, 16);
	if (type == 1)
		ft_pf_buffer_write(state->pbuff, "\033[48;2;");
	else
		ft_pf_buffer_write(state->pbuff, "\033[38;2;");
	if (hexlen == 6)
		ft_pf_write_hex6(state, value);
	else
		ft_pf_write_hex3(state, value);
	if (state->pbuff->capacity > 0)
		state->pbuff->writed = start;
	return (1);
}

void		ft_pf_write_color_reset(t_pf_state *state, int type)
{
	int start;

	start = state->pbuff->writed;
	if (type == 1 || type == 2)
		ft_pf_buffer_write(state->pbuff, "\033[49m");
	if (type == 0 || type == 2)
		ft_pf_buffer_write(state->pbuff, "\033[39m");
	if (state->pbuff->capacity > 0)
		state->pbuff->writed = start;
}

void		ft_pf_extract_color
	(t_pf_state *state, const char **fmt, char color[], int max)
{
	int	i;

	i = -1;
	while (**fmt == '*')
	{
		ft_strncpy(color, va_arg(state->args, char*), max);
		(*fmt)++;
	}
	while (**fmt && ++i < (max - 1) && **fmt != '}')
	{
		color[i] = (*(*fmt)++);
		color[i + 1] = 0;
	}
	if (**fmt == '}')
		++(*fmt);
}
