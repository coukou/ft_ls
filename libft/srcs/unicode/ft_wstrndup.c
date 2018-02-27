/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:20:01 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:32:44 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"
#include "libft/memory.h"
#include <stdlib.h>

wchar_t		*ft_wstrndup(const wchar_t *wstr, size_t n)
{
	wchar_t	*cpy;
	size_t	size;

	size = ft_wstrlen(wstr);
	if (size > n)
		size = n;
	cpy = (wchar_t*)ft_memalloc(sizeof(*cpy) * (size + 1));
	if (!cpy)
		return (NULL);
	cpy = ft_memcpy(cpy, wstr, sizeof(*cpy) * size);
	return (cpy);
}
