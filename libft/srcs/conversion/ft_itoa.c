/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:36:27 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/12 17:34:24 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char *ret;

	ret = ft_strnew(ft_nbrlen(n, 10) + ((n < 0) ? 1 : 0));
	if (!ret)
		return (NULL);
	ft_lltoa(n, 10, ret);
	return (ret);
}
