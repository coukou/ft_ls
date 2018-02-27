/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:27:25 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 18:08:04 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lltoa(long long n, int base, char out[])
{
	if (n < 0 && base == 10)
	{
		out[0] = '-';
		ft_ulltoa(FT_ABS(n), base, out + 1);
	}
	else
		ft_ulltoa(FT_ABS(n), base, out);
}
