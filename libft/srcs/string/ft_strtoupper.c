/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:32:44 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/09 21:37:39 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		iter_toupper(char *s)
{
	*s = ft_toupper(*s);
}

char			*ft_strtoupper(char *str)
{
	ft_striter(str, &iter_toupper);
	return (str);
}
