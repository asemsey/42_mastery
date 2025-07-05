/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:45:40 by asemsey           #+#    #+#             */
/*   Updated: 2024/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	length(const char *s, unsigned int start, size_t len)
{
	if (len > ft_strlen(s) - start)
		return (ft_strlen(s) - start);
	return (len);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (s[0] == '\0' || len == 0 || start >= ft_strlen(s))
	{
		str = (char *)malloc(1);
		if (str == 0)
			return (0);
		str[0] = '\0';
		return (str);
	}
	len = length(s, start, len);
	str = (char *)malloc(len + 1);
	if (str == 0)
		return (0);
	while (i < len && (start + i) < ft_strlen(s))
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
