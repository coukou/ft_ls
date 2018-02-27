/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:32:59 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 23:56:15 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int un;

	un = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = -n;
	}
	if (un / 10 > 0)
		ft_putnbr_fd(un / 10, fd);
	ft_putchar_fd('0' + un % 10, fd);
}
