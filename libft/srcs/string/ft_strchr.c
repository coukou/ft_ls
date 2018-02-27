/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:11:37 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 17:39:24 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(str);
	while (i < len && str[i] != c)
		i++;
	if (str[i] == c)
		return ((char*)&str[i]);
	return (i == len ? NULL : (char*)&str[i]);
}
