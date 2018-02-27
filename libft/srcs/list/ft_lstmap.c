/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 00:05:07 by spopieul          #+#    #+#             */
/*   Updated: 2017/11/13 06:52:18 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *backptr;
	t_list *back;
	t_list *tmp;

	if (lst == NULL)
		return (NULL);
	back = NULL;
	while (lst)
	{
		tmp = f(lst);
		if (tmp != NULL && back == NULL)
		{
			back = tmp;
			backptr = back;
		}
		else if (tmp != NULL)
		{
			back->next = tmp;
			back = back->next;
		}
		lst = lst->next;
	}
	return (backptr);
}
