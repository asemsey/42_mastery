/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:01:07 by asemsey           #+#    #+#             */
/*   Updated: 2023/10/18 11:29:01 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_digits(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	ft_digits_u(unsigned int n, unsigned int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0 && base != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

int	ft_digits_lu(unsigned long n, unsigned int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0 && base != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}
