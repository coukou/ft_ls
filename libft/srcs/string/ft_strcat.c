/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:00:06 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/11 15:39:49 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char *s2)
{
	size_t i;
	size_t offset;

	i = 0;
	offset = ft_strlen(s1);
	while (s2[i])
	{
		s1[offset + i] = s2[i];
		i++;
	}
	s1[offset + i] = '\0';
	return (s1);
}
