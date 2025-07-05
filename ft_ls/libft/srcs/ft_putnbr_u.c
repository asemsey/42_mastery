/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:19:10 by asemsey           #+#    #+#             */
/*   Updated: 2023/10/30 13:46:10 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_u(unsigned int n)
{
	int		i;
	char	s[256];

	i = ft_digits_u(n, 10);
	if (n == 0)
	{
		ft_putchar_fd('0', 1);
		return ;
	}
	s[i--] = '\0';
	while (n > 0)
	{
		s[i--] = (n % 10) + '0';
		n /= 10;
	}
	i = 0;
	while (s[i] != '\0')
		ft_putchar_fd(s[i++], 1);
}
