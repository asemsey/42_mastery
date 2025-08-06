/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:05:20 by asemsey           #+#    #+#             */
/*   Updated: 2025/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// add a list into another linked list at the front
void	ft_lstpushin(t_list **lst, t_list *push)
{
	t_list *l = *lst;
	*lst = push;
	ft_lstadd_back(lst, l);
}
