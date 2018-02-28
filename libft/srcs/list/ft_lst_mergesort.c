/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mergesort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:34:00 by orenkay           #+#    #+#             */
/*   Updated: 2018/02/28 15:59:20 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/list.h"

static t_list	*ft_lst_merge(t_list *a, t_list *b, int reverse, int (*cmp)(void*, void*))
{
	int cond;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	cond = cmp(a->content, b->content) <= 0;
	if ((!reverse) ? cond : !cond)
	{
		a->next = ft_lst_merge(a->next, b, reverse, cmp);
		return (a);
	}
	else
	{
		b->next = ft_lst_merge(a, b->next, reverse, cmp);
		return (b);
	}
}

static void		ft_lst_midsplit(t_list *head, t_list **a, t_list **b)
{
	t_list *fast;
	t_list *slow;

	*a = head;
	if (head == NULL || head->next == NULL)
		*b = NULL;
	else
	{
		slow = head;
		fast = head->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*b = slow->next;
		slow->next = NULL;
	}
}

void			ft_lst_mergesort(t_list **head, int reverse, int (*cmp)(void*, void*))
{
	t_list *a;
	t_list *b;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	ft_lst_midsplit(*head, &a, &b);
	ft_lst_mergesort(&a, reverse, cmp);
	ft_lst_mergesort(&b, reverse, cmp);
	*head = ft_lst_merge(b, a, reverse, cmp);
}
