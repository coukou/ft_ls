/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:29:07 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:25:43 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(const char *s)
{
	size_t len;

	if (s == NULL)
		return (NULL);
	while (ft_isblank(*s) && *s)
		s++;
	if (*s == '\0')
		return (ft_strdup(s));
	len = ft_strlen(s);
	while (ft_isblank(s[--len]))
		;
	return (ft_strndup(s, len + 1));
}
