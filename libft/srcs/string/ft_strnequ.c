/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 00:49:03 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 18:00:20 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (1);
	if (s1 == NULL || s2 == NULL || n == 0)
		return (0);
	return (ft_strncmp(s1, s2, n) == 0);
}
