/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:36:56 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 17:22:12 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t i;

	if (tofind[0] == '\0')
		return ((char*)str);
	while (*str && len > 0)
	{
		i = 0;
		while (tofind[i] && *(str + i) == tofind[i] && len - i > 0)
			i++;
		if (tofind[i] == '\0')
			return ((char*)str);
		str++;
		len--;
	}
	return (NULL);
}
