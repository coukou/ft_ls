/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:46:10 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/26 19:55:57 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"


void		ft_pf_format_s(t_pf_state *state)
{
	t_pf_data	data;
	char		*str;

	if (FT_MASK_EQ(state->length, M_LENGTH_L))
	{
		ft_pf_format_ws(state);
		return ;
	}
	str = va_arg(state->args, char*);
	if (str == 0)
		str = "(null)";
	data.len = ft_strlen(str);
	if (state->precision > -1 && state->precision < (int)data.len)
		data.len = state->precision;
	data.width = state->width;
	if (state->width != -1)
		data.width = FT_ABS(state->width);
	data.width = FT_MIN(data.width - data.len, 0);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	ft_pf_write_s(state, &data, str);
}

void		ft_pf_format_signed(t_pf_state *state)
{
	t_pf_data data;

	if (state->specifier == 'D')
		state->length |= M_LENGTH_L;
	ft_pf_get_signed(state, data.value);
	data.sign = ft_pf_extract_sign(state, data.value);
	data.len = ft_strlen(data.value);
	if (*data.value == '0' && state->precision == 0)
		data.len = 0;
	data.bpad = "";
	data.precision = FT_MIN(state->precision - (int)data.len, 0);
	data.width = ft_pf_get_pad_width(state, &data);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	if (state->precision > -1)
		data.pchar = " ";
	ft_pf_write_data(state, &data);
}

void		ft_pf_format_unsigned(t_pf_state *state)
{
	t_pf_data data;

	if (state->specifier == 'U' || state->specifier == 'O')
		state->length |= M_LENGTH_L;
	ft_pf_get_unsigned(state, data.value);
	data.sign = ft_pf_extract_sign(state, data.value);
	data.sign = "";
	data.len = ft_strlen(data.value);
	if (*data.value == '0' && state->precision == 0)
		data.len = 0;
	data.bpad = ft_pf_get_base_padding(state, &data);
	data.precision = FT_MIN(state->precision - (int)data.len, 0);
	data.width = ft_pf_get_pad_width(state, &data);
	if (ft_tolower(state->specifier) == 'o')
		data.precision -= (int)ft_strlen(data.bpad);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	ft_pf_write_data(state, &data);
}

void		ft_pf_format_n(t_pf_state *state)
{
	void	*ptr;

	if (FT_MASK_EQ(state->length, M_LENGTH_LL) &&
		(ptr = va_arg(state->args, long long*)))
		*((long long*)ptr) = state->pbuff->writed;
	else if (FT_MASK_EQ(state->length, M_LENGTH_L) &&
		(ptr = va_arg(state->args, long*)))
		*((long*)ptr) = state->pbuff->writed;
	else if (FT_MASK_EQ(state->length, M_LENGTH_J) &&
		(ptr = va_arg(state->args, intmax_t*)))
		*((intmax_t*)ptr) = state->pbuff->writed;
	else if (FT_MASK_EQ(state->length, M_LENGTH_T) &&
		(ptr = va_arg(state->args, ptrdiff_t*)))
		*((ptrdiff_t*)ptr) = state->pbuff->writed;
	else if (FT_MASK_EQ(state->length, M_LENGTH_Z) &&
		(ptr = va_arg(state->args, size_t*)))
		*((size_t*)ptr) = state->pbuff->writed;
	else if (FT_MASK_EQ(state->length, M_LENGTH_HH) &&
		(ptr = va_arg(state->args, char*)))
		*((char*)ptr) = state->pbuff->writed;
	else if (FT_MASK_EQ(state->length, M_LENGTH_H) &&
		(ptr = (short*)va_arg(state->args, int*)))
		*((short*)ptr) = state->pbuff->writed;
	else if ((ptr = va_arg(state->args, int*)))
		*((int*)ptr) = state->pbuff->writed;
}
