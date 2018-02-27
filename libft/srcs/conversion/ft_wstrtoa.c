/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:28:33 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/12 20:06:56 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"
#include "libft/string.h"
#include "libft/conversion.h"
#include "libft/memory.h"

void	ft_wstrtoa(const wchar_t *wstr, char out[])
{
	int		i;
	size_t	offset;

	i = -1;
	offset = 0;
	while (wstr[++i])
	{
		ft_wctoa(wstr[i], out + offset);
		offset += ft_wclen(wstr[i]);
	}
	*(out + offset) = 0;
}
