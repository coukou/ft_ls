/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:25:28 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/13 17:27:54 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = -1;
	j = ft_strlen(s);
	while (++i < j--)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
	return (s);
}
