/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cb_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:07:51 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/09 17:14:02 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_cb	*ft_cb_new(size_t size)
{
	t_cb *cb;

	if (!(cb = ft_memalloc(sizeof(*cb))))
		return (NULL);
	if (!(cb->buf = ft_memalloc(size)))
		return (NULL);
	cb->end = cb->buf + size;
	cb->content_size = 0;
	cb->head = cb->buf;
	cb->tail = cb->buf;
	return (cb);
}
