/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cb_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:04:44 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/18 15:24:58 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_cb_read(t_cb *cb, void *data, size_t size)
{
	size_t max;

	max = cb->end - cb->tail;
	while (size > max)
	{
		ft_memcpy(data, cb->tail, max);
		size -= max;
		cb->tail = cb->buf;
		cb->content_size -= max;
		data += max;
	}
	if (size <= max)
	{
		ft_memcpy(data, cb->tail, size);
		cb->tail += size;
		cb->content_size -= size;
		data += size;
	}
	if (cb->tail == cb->end)
		cb->tail = cb->buf;
}
