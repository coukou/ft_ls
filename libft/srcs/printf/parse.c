/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:47:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/25 17:56:32 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		ft_pf_get_width(t_pf_state *state)
{
	if (**state->fmt == '.')
		return (0);
	if (ft_isdigit(**state->fmt))
		state->width = ft_pf_atoi(state->fmt);
	else if (**state->fmt == '*')
	{
		state->width = va_arg(state->args, int);
		(*state->fmt)++;
	}
	else
		return (0);
	return (1);
}

int		ft_pf_get_precision(t_pf_state *state)
{
	if (**state->fmt != '.')
		return (0);
	(*state->fmt)++;
	if (**state->fmt == '*')
	{
		state->precision = va_arg(state->args, int);
		(*state->fmt)++;
	}
	else
		state->precision = ft_pf_atoi(state->fmt);
	return (1);
}

int		ft_pf_get_length(t_pf_state *state)
{
	if (**state->fmt == 'l' && *((*state->fmt) + 1) != 'l')
		state->length |= M_LENGTH_L;
	else if (**state->fmt == 'l' && (*state->fmt)++)
		state->length |= M_LENGTH_LL;
	else if (**state->fmt == 'h' && *((*state->fmt) + 1) != 'h')
		state->length |= M_LENGTH_H;
	else if (**state->fmt == 'h' && (*state->fmt)++)
		state->length |= M_LENGTH_HH;
	else if (**state->fmt == 'j')
		state->length |= M_LENGTH_J;
	else if (**state->fmt == 'z')
		state->length |= M_LENGTH_Z;
	else if (**state->fmt == 't')
		state->length |= M_LENGTH_T;
	else if (**state->fmt == 'L')
		state->length |= M_LENGTH_L_;
	else
		return (0);
	(*state->fmt)++;
	return (1);
}

int		ft_pf_get_flags(t_pf_state *state)
{
	int result;

	result = 0;
	while (**state->fmt)
	{
		if (**state->fmt == '+')
			state->flags |= M_FLAG_PLUS;
		else if (**state->fmt == '-')
			state->flags |= M_FLAG_MINUS;
		else if (**state->fmt == ' ')
			state->flags |= M_FLAG_SPACE;
		else if (**state->fmt == '#')
			state->flags |= M_FLAG_HASH;
		else if (**state->fmt == '0')
			state->flags |= M_FLAG_ZERO;
		else
			return (result);
		(*state->fmt)++;
		result = 1;
	}
	return (result);
}
