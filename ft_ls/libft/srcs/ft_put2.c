/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:33:05 by asemsey           #+#    #+#             */
/*   Updated: 2023/10/30 16:44:30 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_put_p(void *p, char *base)
{
	unsigned long	n;
	int				len;

	n = (unsigned long)p;
	ft_putstr_fd("0x", 1);
	len = ft_putptr(n, base) + 2;
	return (len);
}

int	ft_putptr(unsigned long n, char *base)
{
	int		i;
	int		len;
	char	s[256];

	i = ft_digits_lu(n, 16);
	if (n == 0)
	{
		ft_putchar_fd(base[0], 1);
		return (1);
	}
	len = i;
	s[i--] = '\0';
	while (n > 0)
	{
		s[i--] = base[n % 16];
		n /= 16;
	}
	i = 0;
	while (s[i] != '\0')
		ft_putchar_fd(s[i++], 1);
	return (len);
}
