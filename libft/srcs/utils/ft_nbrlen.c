/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:28:23 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:33:04 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_nbrlen(long long n, int base)
{
	size_t i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}
