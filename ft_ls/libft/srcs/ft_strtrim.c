/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:06:30 by asemsey           #+#    #+#             */
/*   Updated: 2024/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	contains(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	j = 0;
	if (set[0] == '\0' || s1[0] == '\0')
		return (-1);
	while (s1[i] != '\0' && contains(set, s1[i]) == 1)
		i++;
	while (s1[i + count + j] != '\0')
	{
		while (s1[i + count] != '\0' && contains(set, s1[i + count]) == 0)
			count++;
		while (s1[i + count + j] != '\0'
			&& contains(set, s1[i + count + j]) == 1)
			j++;
		if (s1[i + count + j] == '\0')
			return (count);
		count += j;
		j = 0;
	}
	return (count);
}

static char	*allocate(const char *s1, const char *set, int len)
{
	char	*s;
	size_t	i;

	i = 0;
	if (len == 0 || s1[0] == '\0')
	{
		s = (char *)malloc(1);
		if (s == 0)
			return (0);
		s[0] = '\0';
		return (s);
	}
	if (set[0] == '\0')
	{
		s = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
		if (s == 0)
			return (0);
		while (i <= ft_strlen(s1))
		{
			s[i] = s1[i];
			i++;
		}
		return (s);
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	int		k;
	char	*s;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	k = count(s1, set);
	if (k < 1)
		return (s = allocate(s1, set, k));
	else
		s = (char *)malloc((k + 1) * sizeof(char));
	if (s == 0)
		return (0);
	while (s1[i] != '\0' && contains(set, s1[i]) == 1)
		i++;
	while (j < k)
	{
		s[j] = s1[i + j];
		j++;
	}
	s[j] = '\0';
	return (s);
}
