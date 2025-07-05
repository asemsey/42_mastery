/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:12:53 by asemsey           #+#    #+#             */
/*   Updated: 2023/10/30 10:07:13 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_put_c(char c);
int		ft_put_s(char *s);
int		ft_put_i(int n);
int		ft_put_x(unsigned int n, char *base);
int		ft_put_u(unsigned int n);
int		ft_put_c(char c);
int		ft_put_p(void *p, char *base);
int		ft_putptr(unsigned long n, char *base);

int		ft_printf(const char *format, ...);

#endif