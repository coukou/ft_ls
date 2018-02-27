/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:04:08 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/26 19:57:08 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void		ft_pf_write_padding(t_pf_state *state, int width, char *pchar)
{
	while (width-- > 0)
		ft_pf_buffer_write_n(state->pbuff, pchar, 1);
}

void		ft_pf_write_data(t_pf_state *state, t_pf_data *data)
{
	if (FT_MASK_EQ(state->flags, M_FLAG_MINUS) || state->width < -1)
	{
		ft_pf_buffer_write(state->pbuff, data->sign);
		ft_pf_buffer_write(state->pbuff, data->bpad);
		ft_pf_write_padding(state, data->precision, "0");
		ft_pf_buffer_write_n(state->pbuff, data->value, data->len);
		ft_pf_write_padding(state, data->width, " ");
	}
	else
	{
		if (*data->pchar == '0')
		{
			ft_pf_buffer_write(state->pbuff, data->bpad);
			ft_pf_buffer_write(state->pbuff, data->sign);
			ft_pf_write_padding(state, data->width, data->pchar);
		}
		if (*data->pchar != '0')
		{
			ft_pf_write_padding(state, data->width, data->pchar);
			ft_pf_buffer_write(state->pbuff, data->sign);
			ft_pf_buffer_write(state->pbuff, data->bpad);
		}
		ft_pf_write_padding(state, data->precision, "0");
		ft_pf_buffer_write_n(state->pbuff, data->value, data->len);
	}
}

void		ft_pf_write_s(t_pf_state *state, t_pf_data *data, char *str)
{
	if (!FT_MASK_EQ(state->flags, M_FLAG_MINUS) && state->width > 0)
		ft_pf_write_padding(state, data->width, data->pchar);
	ft_pf_buffer_write_n(state->pbuff, str, data->len);
	if (FT_MASK_EQ(state->flags, M_FLAG_MINUS) || state->width < -1)
		ft_pf_write_padding(state, data->width, " ");
}

void		ft_pf_write_ws(t_pf_state *state, t_pf_data *data, wchar_t *wstr)
{
	char	tmp[5];
	int		i;
	size_t	total;
	size_t	wclen;

	i = -1;
	if (!FT_MASK_EQ(state->flags, M_FLAG_MINUS) && state->width > 0)
		ft_pf_write_padding(state, data->width, data->pchar);
	total = 0;
	while (wstr[++i])
	{
		wclen = ft_wclen(wstr[i]);
		total += wclen;
		if (total > data->len)
			break ;
		ft_wctoa(wstr[i], tmp);
		ft_pf_buffer_write_n(state->pbuff, tmp, wclen);
	}
	if (FT_MASK_EQ(state->flags, M_FLAG_MINUS) || state->width < -1)
		ft_pf_write_padding(state, data->width, " ");
}
