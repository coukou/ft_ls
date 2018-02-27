/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:11:37 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 17:49:06 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t len;

	len = ft_strlen((char*)str) + 1;
	while (len--)
	{
		if (str[len] == c)
			return ((char*)&str[len]);
	}
	return (NULL);
}
