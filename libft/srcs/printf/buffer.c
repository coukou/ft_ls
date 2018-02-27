/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:48:16 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/25 18:10:09 by orenkay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

void	ft_pf_buffer_flush(t_pf_buffer *buffer)
{
	if (buffer->offset == 0)
		return ;
	write(1, buffer->data, buffer->offset);
	buffer->offset = 0;
}

void	ft_pf_buffer_write_n(t_pf_buffer *buffer, char *data, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (buffer->capacity > 0 && buffer->offset == buffer->capacity)
			ft_pf_buffer_flush(buffer);
		buffer->data[buffer->offset++] = ((unsigned char*)data)[i++];
		buffer->writed++;
	}
}

void	ft_pf_buffer_write(t_pf_buffer *buffer, char *data)
{
	ft_pf_buffer_write_n(buffer, data, ft_strlen((const char*)data));
}
