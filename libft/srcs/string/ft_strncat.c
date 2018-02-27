/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:03:44 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/11 15:44:53 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char *s2, size_t n)
{
	size_t i;
	size_t offset;

	i = 0;
	offset = ft_strlen(s1);
	while (s2[i] && i < n)
	{
		s1[offset + i] = s2[i];
		i++;
	}
	s1[offset + i] = '\0';
	return (s1);
}
