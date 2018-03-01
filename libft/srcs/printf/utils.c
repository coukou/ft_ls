/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 16:59:15 by spopieul          #+#    #+#             */
/*   Updated: 2018/03/01 12:25:08 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		ft_pf_atoi(const char **fmt)
{
	int res;
	int n;

	res = 0;
	n = 1;
	while (ft_isspace(**fmt))
		(*fmt)++;
	if (**fmt == '-')
		n = -1;
	if (**fmt == '-' || **fmt == '+')
		(*fmt)++;
	while (ft_isdigit(**fmt))
	{
		res *= 10;
		res += **fmt - '0';
		(*fmt)++;
	}
	return (res * n);
}

char	*ft_pf_get_base_padding(t_pf_state *state, t_pf_data *data)
{
	int s;

	if (!FT_MASK_EQ(state->flags, M_FLAG_HASH))
		return ("");
	s = state->specifier;
	if (*data->value == '0' && ft_tolower(s) != 'o')
		return ("");
	if (*data->value == '0' && ft_tolower(s) == 'o' && state->precision == -1)
		return ("");
	if (s == 'x')
		return ("0x");
	else if (s == 'X')
		return ("0X");
	else if (ft_tolower(s) == 'o')
		return ("0");
	else
		return ("");
}

size_t	ft_pf_get_pad_width(t_pf_state *state, t_pf_data *data)
{
	int width;
	int slen;
	int dlen;
	int blen;

	dlen = (int)data->len + data->precision;
	slen = (int)ft_strlen(data->sign);
	blen = (int)ft_strlen(data->bpad);
	width = (state->width < -1) ? FT_ABS(state->width) : state->width;
	return (FT_MAX(width - dlen - slen - blen, 0));
}

int		ft_pf_get_base(t_pf_state *state)
{
	if (state->specifier == 'x' || state->specifier == 'X')
		return (16);
	else if (state->specifier == 'o' || state->specifier == 'O')
		return (8);
	else if (state->specifier == 'b' || state->specifier == 'B')
		return (2);
	else
		return (10);
}

char	*ft_pf_extract_sign(t_pf_state *state, char data[])
{
	int i;

	i = -1;
	if (*data == '-')
	{
		while (data[++i])
			data[i] = data[i + 1];
		return ("-");
	}
	else if (FT_MASK_EQ(state->flags, M_FLAG_PLUS))
		return ("+");
	else if (FT_MASK_EQ(state->flags, M_FLAG_SPACE))
		return (" ");
	else
		return ("");
}
