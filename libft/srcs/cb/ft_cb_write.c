/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cb_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:05:10 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/18 15:25:12 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_cb_write(t_cb *cb, void *data, size_t size)
{
	size_t max;

	max = cb->end - cb->head;
	while (size > max)
	{
		ft_memcpy(cb->head, data, max);
		size -= max;
		cb->head = cb->buf;
		cb->content_size += max;
		data += max;
	}
	if (size <= max)
	{
		ft_memcpy(cb->head, data, size);
		cb->head += size;
		cb->content_size += size;
		data += size;
	}
	if (cb->content_size > (size_t)(cb->end - cb->buf))
		cb->content_size = cb->end - cb->buf;
	if (cb->head == cb->end)
		cb->head = cb->buf;
}
