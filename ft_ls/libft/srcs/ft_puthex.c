/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:31:33 by asemsey           #+#    #+#             */
/*   Updated: 2023/10/30 13:46:33 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthex(unsigned int n, char *base)
{
	int		i;
	char	s[256];

	i = ft_digits_u(n, 16);
	if (n == 0)
	{
		ft_putchar_fd(base[0], 1);
		return ;
	}
	s[i--] = '\0';
	while (n > 0)
	{
		s[i--] = base[n % 16];
		n /= 16;
	}
	i = 0;
	while (s[i] != '\0')
		ft_putchar_fd(s[i++], 1);
}
