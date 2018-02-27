/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:00:35 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:31:58 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/unicode.h"
#include "libft/memory.h"
#include <stdlib.h>

wchar_t	*ft_wstrdup(const wchar_t *wstr)
{
	wchar_t	*cpy;
	size_t	size;

	size = ft_wstrlen(wstr);
	cpy = (wchar_t*)ft_memalloc(sizeof(*cpy) * (size + 1));
	if (!cpy)
		return (NULL);
	cpy = ft_memcpy(cpy, wstr, sizeof(*cpy) * size);
	return (cpy);
}
