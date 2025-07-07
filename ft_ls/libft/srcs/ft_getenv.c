/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:41:25 by asemsey           #+#    #+#             */
/*   Updated: 2024/09/03 09:48:03 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_match(char *name, char *var, int namelen) {
	char *content = ft_strchr(var, '=');
	if (content && (content - var) == namelen)
		return !ft_strncmp(name, var, namelen);
	return 0;
}

// not malloced
char	*ft_getenv(char *name, char **env)
{
	int i;
	int match;
	int namelen;
	
	if (!name || !*name)
	return NULL;
	if (!env || !*env)
	return NULL;
	
	namelen = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		match = ft_match(name, env[i], namelen);
		if (match)
			return (char *)(env[i] + namelen + 1);
		i++;
	}
	return NULL;
}
