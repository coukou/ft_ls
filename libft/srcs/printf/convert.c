/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:48:00 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/25 17:56:16 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void		ft_pf_get_signed(t_pf_state *state, char out[])
{
	if (FT_MASK_EQ(state->length, M_LENGTH_LL))
		ft_lltoa(va_arg(state->args, long long), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_L))
		ft_lltoa(va_arg(state->args, long), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_J))
		ft_lltoa(va_arg(state->args, intmax_t), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_T))
		ft_lltoa(va_arg(state->args, ptrdiff_t), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_Z))
		ft_lltoa(va_arg(state->args, size_t), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_HH))
		ft_lltoa((char)va_arg(state->args, int), 10, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_H))
		ft_lltoa((short)va_arg(state->args, int), 10, out);
	else
		ft_lltoa(va_arg(state->args, int), 10, out);
}

void		ft_pf_get_unsigned(t_pf_state *state, char out[])
{
	int b;

	b = ft_pf_get_base(state);
	if (FT_MASK_EQ(state->length, M_LENGTH_LL))
		ft_ulltoa(va_arg(state->args, unsigned long long), b, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_L))
		ft_ulltoa(va_arg(state->args, unsigned long), b, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_J))
		ft_ulltoa(va_arg(state->args, uintmax_t), b, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_T))
		ft_ulltoa(va_arg(state->args, ptrdiff_t), b, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_Z))
		ft_ulltoa(va_arg(state->args, size_t), b, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_HH))
		ft_ulltoa((unsigned char)va_arg(state->args, unsigned int), b, out);
	else if (FT_MASK_EQ(state->length, M_LENGTH_H))
		ft_ulltoa((unsigned short)va_arg(state->args, unsigned int), b, out);
	else
		ft_ulltoa(va_arg(state->args, unsigned int), b, out);
	if (ft_islower(state->specifier))
		ft_strtolower(out);
}
