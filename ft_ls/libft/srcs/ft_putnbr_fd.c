/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:24:32 by asemsey           #+#    #+#             */
/*   Updated: 2024/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_cases(int nbr, int fd)
{
	if (nbr == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (nbr == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		i;

	i = 0;
	if (n == 0 || n == -2147483648)
	{
		ft_cases(n, fd);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	while (n > 0)
	{
		str[i] = '0' + (n % 10);
		n /= 10;
		i++;
	}
	while (i > 0)
	{
		i--;
		write(fd, &str[i], 1);
	}
}
