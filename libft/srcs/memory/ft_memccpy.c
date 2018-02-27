/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:59:40 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 17:15:48 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *dptr;
	unsigned char *sptr;

	dptr = (unsigned char*)dst;
	sptr = (unsigned char*)src;
	while (n--)
	{
		*dptr++ = *sptr++;
		if (*(sptr - 1) == (unsigned char)c)
			return (dptr);
	}
	return (NULL);
}
