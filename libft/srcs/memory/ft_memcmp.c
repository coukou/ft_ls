/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:16:19 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 18:58:14 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s1_ptr;
	unsigned char *s2_ptr;

	if (n == 0)
		return (0);
	s1_ptr = (unsigned char*)s1;
	s2_ptr = (unsigned char*)s2;
	while (*s1_ptr == *s2_ptr && --n)
	{
		s1_ptr++;
		s2_ptr++;
	}
	return (*s1_ptr - *s2_ptr);
}
