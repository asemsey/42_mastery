/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpopout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:05:20 by asemsey           #+#    #+#             */
/*   Updated: 2025/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// pop a node out from linked list by content ptr and return it
t_list	*ft_lstpopout(t_list **lst, void *target)
{
	if (!(*lst))
		return *lst;
	t_list *node;
	t_list *out;
	out = (*lst);
	node = (*lst);
	while (out) {
		if (out->content == target)
			break;
		out = out->next;
		if (node->next != out)
			node = node->next;
	}
	if (node->next == out)
		node->next = out->next;
	else
		(*lst) = (*lst)->next;
	out->next = NULL;
	return out;
}
