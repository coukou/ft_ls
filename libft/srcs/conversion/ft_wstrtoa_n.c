/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtoa_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:28:33 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/13 18:08:15 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"
#include "libft/string.h"
#include "libft/conversion.h"
#include "libft/memory.h"

static size_t	get_final_size(const wchar_t *wstr, size_t max)
{
	int		i;
	size_t	len;
	size_t	wc_len;

	i = -1;
	len = 0;
	while (wstr[++i])
	{
		wc_len = ft_wclen(wstr[i]);
		if (len + wc_len > max)
			return (len);
		len += wc_len;
	}
	return (len);
}

void			ft_wstrtoa_n(const wchar_t *wstr, size_t n, char out[])
{
	int		i;
	size_t	size;
	size_t	offset;
	size_t	wc_len;

	size = get_final_size(wstr, n);
	i = -1;
	offset = 0;
	while (wstr[++i])
	{
		wc_len = ft_wclen(wstr[i]);
		if (offset + wc_len > size)
			break ;
		ft_wctoa(wstr[i], out + offset);
		offset += wc_len;
	}
	*(out + offset) = 0;
}
