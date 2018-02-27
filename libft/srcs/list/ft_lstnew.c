/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 18:18:44 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/14 17:52:26 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list *n;

	n = (t_list*)ft_memalloc(sizeof(*n));
	if (n == NULL)
		return (NULL);
	if (content != NULL)
	{
		n->content = ft_memalloc(content_size);
		if (n->content == NULL)
			return (NULL);
		ft_memcpy(n->content, content, content_size);
		n->content_size = content_size;
	}
	else
	{
		n->content = NULL;
		n->content_size = 0;
	}
	n->next = NULL;
	return (n);
}
