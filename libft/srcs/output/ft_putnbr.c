/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:28:13 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/11 15:38:56 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int un;

	un = n;
	if (n < 0)
	{
		ft_putchar('-');
		un = -n;
	}
	if (un / 10 > 0)
		ft_putnbr(un / 10);
	ft_putchar('0' + un % 10);
}
