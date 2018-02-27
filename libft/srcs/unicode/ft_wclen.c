/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wclen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 13:34:44 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/11 12:31:38 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/unicode.h>
#include <wchar.h>
#include <stdlib.h>

size_t	ft_wclen(wchar_t c)
{
	if (c >= WCHAR_1_MIN && c <= WCHAR_1_MAX)
		return (1);
	else if (c >= WCHAR_2_MIN && c <= WCHAR_2_MAX)
		return (2);
	else if (c >= WCHAR_3_MIN && c <= WCHAR_3_MAX)
		return (3);
	else if (c >= WCHAR_4_MIN && c <= WCHAR_4_MAX)
		return (4);
	else
		return (0);
}
