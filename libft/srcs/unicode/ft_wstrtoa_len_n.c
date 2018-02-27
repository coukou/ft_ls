/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtoa_len_n.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 11:19:28 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/13 15:01:18 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"

size_t	ft_wstrtoa_len_n(const wchar_t *wstr, size_t n)
{
	int		i;
	size_t	len;
	size_t	wc_len;

	i = -1;
	len = 0;
	while (wstr[++i])
	{
		wc_len = ft_wclen(wstr[i]);
		if (len + wc_len > n)
			break ;
		len += wc_len;
	}
	return (len);
}
