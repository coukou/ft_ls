/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 06:32:21 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:31:19 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t len)
{
	char	*dup;
	size_t	max;

	if ((max = ft_strlen(str)) < len)
		len = max;
	dup = ft_strnew(len);
	if (dup == NULL)
		return (NULL);
	while (len--)
		dup[len] = str[len];
	return (dup);
}
