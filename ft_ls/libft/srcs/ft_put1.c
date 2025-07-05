/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:48:53 by asemsey           #+#    #+#             */
/*   Updated: 2023/10/30 16:44:11 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_put_c(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_put_s(char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	ft_put_i(int n)
{
	ft_putnbr_fd(n, 1);
	return (ft_digits(n));
}

int	ft_put_x(unsigned int n, char *base)
{
	ft_puthex(n, base);
	return (ft_digits_u(n, 16));
}

int	ft_put_u(unsigned int n)
{
	ft_putnbr_u(n);
	return (ft_digits_u(n, 10));
}
