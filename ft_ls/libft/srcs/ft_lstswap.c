/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:05:20 by asemsey           #+#    #+#             */
/*   Updated: 2025/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"


void	ft_lstswap(t_list **lst)
{
	int	size = ft_lstsize(*lst);
	t_list *l1;
	t_list *next;
	if (size < 2)
		return ;
	
	l1 = (*lst);
	*lst = (*lst)->next;
	next = (*lst)->next;

	l1->next = next;
	(*lst)->next = l1;
}
