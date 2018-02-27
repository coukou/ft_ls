/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:35:50 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/13 18:08:43 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"
#include "libft/string.h"

static void		wctoa_1(wchar_t wc, char out[])
{
	out[0] = wc & 0x7F;
}

static void		wctoa_2(wchar_t wc, char out[])
{
	out[0] = 0xC0 | ((wc >> 6) & 0x1F);
	out[1] = 0x80 | (wc & 0x3F);
}

static void		wctoa_3(wchar_t wc, char out[])
{
	out[0] = 0xE0 | ((wc >> 12) & 0xF);
	out[1] = 0x80 | ((wc >> 6) & 0x3F);
	out[2] = 0x80 | (wc & 0x3F);
}

static void		wctoa_4(wchar_t wc, char out[])
{
	out[0] = 0xF0 | ((wc >> 18) & 0x7);
	out[1] = 0x80 | ((wc >> 12) & 0x3F);
	out[2] = 0x80 | ((wc >> 6) & 0x3F);
	out[3] = 0x80 | (wc & 0x3F);
}

void			ft_wctoa(wchar_t wc, char out[])
{
	int wlen;

	wlen = ft_wclen(wc);
	if (wlen == 1)
		wctoa_1(wc, out);
	if (wlen == 2)
		wctoa_2(wc, out);
	if (wlen == 3)
		wctoa_3(wc, out);
	if (wlen == 4)
		wctoa_4(wc, out);
}
