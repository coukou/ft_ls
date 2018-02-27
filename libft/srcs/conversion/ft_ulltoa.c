/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:27:25 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 18:14:19 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ulltoa(unsigned long long n, int base, char out[])
{
	int i;

	if (base < 2 || base > 16)
		return ;
	i = -1;
	if (n == 0)
		out[++i] = '0';
	while (n)
	{
		out[++i] = FT_CHAR_BASE[n % base];
		n /= base;
	}
	out[i + 1] = '\0';
	ft_strrev(out);
}
