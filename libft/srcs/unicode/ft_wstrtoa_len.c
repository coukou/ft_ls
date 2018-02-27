/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrtoa_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 11:19:28 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/13 11:23:07 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"

size_t	ft_wstrtoa_len(const wchar_t *wstr)
{
	int		i;
	size_t	len;

	i = -1;
	len = 0;
	while (wstr[++i])
		len += ft_wclen(wstr[i]);
	return (len);
}
