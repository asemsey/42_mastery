/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:11:08 by asemsey           #+#    #+#             */
/*   Updated: 2023/10/30 16:43:48 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_next_type(char *f);
static int	ft_puttype(char c, va_list	args);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*f;
	int		i;
	int		len;

	i = 0;
	f = (char *)format;
	len = 0;
	va_start(args, format);
	while (f[i] != '%' && f[i] != '\0')
		ft_putchar_fd(f[i++], 1);
	len += i;
	while (ft_next_type(f)[0] != '\0')
	{
		f = ft_next_type(f);
		len += ft_puttype(f[0], args);
		f++;
		i = 0;
		while (f[i] != '%' && f[i] != '\0')
			ft_putchar_fd(f[i++], 1);
		len += i;
	}
	va_end(args);
	return (len);
}

static int	ft_puttype(char c, va_list args)
{
	if (c == '%')
		return (ft_put_c('%'));
	if (c == 's')
		return (ft_put_s(va_arg(args, char *)));
	if (c == 'c')
		return (ft_put_c(va_arg(args, int)));
	if (c == 'i' || c == 'd')
		return (ft_put_i(va_arg(args, int)));
	if (c == 'X')
		return (ft_put_x(va_arg(args, unsigned int), "0123456789ABCDEF"));
	if (c == 'x')
		return (ft_put_x(va_arg(args, unsigned int), "0123456789abcdef"));
	if (c == 'p')
		return (ft_put_p(va_arg(args, void *), "0123456789abcdef"));
	if (c == 'u')
		return (ft_put_u(va_arg(args, unsigned int)));
	return (0);
}

// returns the adress of the next %_ in the string
static char	*ft_next_type(char *f)
{
	int		i;

	i = 0;
	while (f[i] != '\0')
	{
		if (f[i] == '%' && f[i + 1] != '\0')
			return (&f[i + 1]);
		i++;
	}
	return ("");
}
