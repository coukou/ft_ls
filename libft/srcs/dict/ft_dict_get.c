/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 12:14:19 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/27 12:40:40 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dict.h"
#include "libft/string.h"

void	*ft_dict_get(t_dict *dict, char *key)
{
	while (dict)
	{
		if (ft_strequ(dict->key, key))
			return (dict->value);
		dict = dict->next;
	}
	return (NULL);
}
