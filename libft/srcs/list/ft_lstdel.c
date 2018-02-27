/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 21:47:36 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/12 22:47:15 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *tmp;
	t_list *next;

	if (*alst == NULL)
		return ;
	next = (*alst)->next;
	while (next)
	{
		tmp = next;
		next = tmp->next;
		ft_lstdelone(&tmp, del);
	}
	ft_lstdelone(alst, del);
}
