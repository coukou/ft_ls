/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:25:00 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/13 17:28:33 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		iter_tolower(char *s)
{
	*s = ft_tolower(*s);
}

char			*ft_strtolower(char *str)
{
	ft_striter(str, &iter_tolower);
	return (str);
}
