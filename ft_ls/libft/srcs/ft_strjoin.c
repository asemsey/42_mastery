/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:08:58 by asemsey           #+#    #+#             */
/*   Updated: 2024/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s;
	size_t	n;

	if (!s1 && !s2)
		return (NULL);
	n = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = (char *)malloc(n);
	if (s == 0)
		return (0);
	s[0] = '\0';
	if (s1 && s1[0] != '\0')
		ft_strlcat(s, s1, n);
	if (s2 && s2[0] != '\0')
		ft_strlcat(s, s2, n);
	return (s);
}
