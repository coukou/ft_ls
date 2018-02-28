/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:36:08 by spopieul          #+#    #+#             */
/*   Updated: 2018/02/28 14:47:23 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/list.h"

void	*ft_lstpop(t_list **head)
{
	t_list	*tmp;
	void	*ret;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	*head = (*head)->next;
	ret = tmp->content;
	free(tmp);
	return (ret);
}
