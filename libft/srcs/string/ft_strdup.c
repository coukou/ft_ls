/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:42:52 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 17:05:27 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	size_t	size;

	size = ft_strlen(str);
	cpy = (char*)malloc(sizeof(*cpy) * size + 1);
	if (!cpy)
		return (NULL);
	cpy = ft_strcpy(cpy, str);
	return (cpy);
}
