/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:43:46 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/25 18:01:41 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void		ft_pf_format_wc(t_pf_state *state)
{
	wchar_t		tmp;
	t_pf_data	data;

	tmp = va_arg(state->args, wchar_t);
	ft_wctoa(tmp, data.value);
	data.len = ft_wclen(tmp);
	data.bpad = "";
	data.precision = 0;
	data.sign = "";
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	data.width = ft_pf_get_pad_width(state, &data);
	ft_pf_write_data(state, &data);
}

void		ft_pf_format_c(t_pf_state *state)
{
	t_pf_data data;

	if (FT_MASK_EQ(state->length, M_LENGTH_L))
	{
		ft_pf_format_wc(state);
		return ;
	}
	data.value[0] = (char)va_arg(state->args, int);
	data.len = 1;
	data.bpad = "";
	data.precision = 0;
	data.sign = "";
	data.width = ft_pf_get_pad_width(state, &data);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	ft_pf_write_data(state, &data);
}

void		ft_pf_format_unknown(t_pf_state *state)
{
	t_pf_data data;

	data.value[0] = state->specifier;
	data.len = 1;
	data.bpad = "";
	data.precision = 0;
	data.sign = "";
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	data.width = ft_pf_get_pad_width(state, &data);
	ft_pf_write_data(state, &data);
}

void		ft_pf_format_p(t_pf_state *state)
{
	t_pf_data data;

	ft_lltoa(va_arg(state->args, intptr_t), 16, data.value);
	ft_strtolower(data.value);
	data.len = (state->precision == 0) ? 0 : ft_strlen(data.value);
	data.bpad = "0x";
	data.precision = FT_MIN(state->precision - data.len, 0);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	data.sign = "";
	data.width = FT_MIN(FT_ABS(state->width) - (data.len + 2), 0);
	ft_pf_write_data(state, &data);
}

void		ft_pf_format_ws(t_pf_state *state)
{
	t_pf_data	data;
	wchar_t		*wstr;

	wstr = va_arg(state->args, wchar_t*);
	if (wstr == 0)
		wstr = L"(null)";
	if (state->precision > -1)
		data.len = ft_wstrtoa_len_n(wstr, state->precision);
	else
		data.len = ft_wstrtoa_len(wstr);
	data.width = state->width;
	if (state->width != -1)
		data.width = FT_ABS(state->width);
	data.width = FT_MIN(data.width - data.len, 0);
	data.pchar = (FT_MASK_EQ(state->flags, M_FLAG_ZERO) ? "0" : " ");
	ft_pf_write_ws(state, &data, wstr);
}
