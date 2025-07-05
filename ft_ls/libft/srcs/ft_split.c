/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:38:39 by asemsey           #+#    #+#             */
/*   Updated: 2024/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count(const char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s && s[i] == c)
		i++;
	while (s && s[i] != '\0')
	{
		if (s[i] != c)
			n++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (n);
}

static char	*copy(char	*s, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc((end - start + 1) * sizeof(char));
	if (str == 0)
		return (0);
	while (start < end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

static int	write_all(char **strs, const char *s, char c)
{
	int	i;
	int	j;
	int	start;
	int	len;

	len = (int)ft_strlen(s);
	i = -1;
	j = 0;
	start = -1;
	while (++i <= len && count(s, c) != 0)
	{
		if (s[i] != c && start < 0)
			start = i;
		else if (start >= 0 && (s[i] == c || i == len))
		{
			strs[j++] = copy((char *)s, start, i);
			start = -1;
			if (strs[j - 1] == 0)
				return (j - 1);
		}
	}
	strs[count(s, c)] = 0;
	return (-1);
}

static void	free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		j;

	if (!s)
		return (NULL);
	if (!*s)
	{
		strs = (char **)malloc(sizeof(char *));
		if (strs == 0)
			return (0);
		strs[0] = 0;
		return (strs);
	}
	strs = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (strs == 0 || !s)
		return (0);
	j = write_all(strs, s, c);
	if (j >= 0)
	{
		free_all(strs);
		return (0);
	}
	return (strs);
}
