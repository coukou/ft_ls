/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:45:10 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 17:05:18 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenc(const char *s, int c)
{
	size_t len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}
