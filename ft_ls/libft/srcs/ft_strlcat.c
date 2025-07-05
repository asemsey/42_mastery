/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:55:34 by asemsey           #+#    #+#             */
/*   Updated: 2024/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static unsigned int	ft_count(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
		j++;
	if (size < i)
		return (j + size);
	else
		return (i + j);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	r;

	i = 0;
	j = 0;
	r = ft_count(dst, src, dstsize);
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (src[j] != '\0' && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (r);
}
