/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:30:13 by asemsey           #+#    #+#             */
/*   Updated: 2023/10/30 13:42:19 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cases(int n, char *str);
// static int	ft_digits(int n);

//uppercase
char	*ft_itoa_x1(int n)
{
	int		i;
	char	*s;
	char	*base;

	base = "0123456789ABCDEF";
	i = ft_digits(n);
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (0);
	ft_cases(n, s);
	if (n == 0 || n == -2147483648)
		return (s);
	s[i--] = '\0';
	if (n < 0)
	{
		n = -n;
		s[0] = '-';
	}
	while (n > 0)
	{
		s[i--] = base[n % 16];
		n /= 16;
	}
	return (s);
}

//lowercase
char	*ft_itoa_x2(int n)
{
	int		i;
	char	*s;
	char	*base;

	base = "0123456789abcdef";
	i = ft_digits(n);
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (0);
	ft_cases(n, s);
	if (n == 0 || n == -2147483648)
		return (s);
	s[i--] = '\0';
	if (n < 0)
	{
		n = -n;
		s[0] = '-';
	}
	while (n > 0)
	{
		s[i--] = base[n % 16];
		n /= 16;
	}
	return (s);
}

// static int	ft_digits(int n)
// {
// 	int	len;

// 	len = 0;
// 	if (n == 0)
// 		return (1);
// 	if (n == -2147483648)
// 		return (9);
// 	if (n < 0)
// 	{
// 		n = -n;
// 		len++;
// 	}
// 	while (n != 0)
// 	{
// 		len++;
// 		n /= 16;
// 	}
// 	return (len);
// }

static void	ft_cases(int n, char *str)
{
	char	*min;
	int		i;

	i = 0;
	min = "-80000000";
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	if (n == -2147483648)
	{
		while (min[i] != '\0')
		{
			str[i] = min[i];
			i++;
		}
		str[i] = '\0';
	}
}
