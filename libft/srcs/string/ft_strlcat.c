/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:40:05 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/26 01:19:07 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	offset;
	size_t	slen;
	int		left;

	offset = ft_strlen(dst);
	slen = ft_strlen(src);
	left = size - offset;
	while (*src && left > 1 && left--)
		*((dst++) + offset) = *(src++);
	*(dst + offset) = '\0';
	return (left > 0 ? (offset + slen) : (size + slen));
}
