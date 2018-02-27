/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:41:53 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/09 16:57:22 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CB_H
# define LIBFT_CB_H

# include <stdlib.h>

typedef struct		s_cb
{
	void			*buf;
	void			*end;
	size_t			content_size;
	void			*head;
	void			*tail;
}					t_cb;

void				ft_cb_read(t_cb *cb, void *data, size_t size);
void				ft_cb_write(t_cb *cb, void *data, size_t size);
t_cb				*ft_cb_new(size_t size);

#endif
