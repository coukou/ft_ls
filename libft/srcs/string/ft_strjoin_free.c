/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 00:59:57 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/25 01:11:42 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(const char *s1, const char *s2)
{
	char *out;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	out = ft_strjoin(s1, s2);
	ft_strdel((char**)&s1);
	ft_strdel((char**)&s2);
	return (out);
}
