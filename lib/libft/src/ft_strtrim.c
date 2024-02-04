/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:23:46 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/06/30 18:22:18 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	isset(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*trim_ini(char *dup, const char *set)
{
	while (isset(*(dup), set))
	{
		ft_memmove(dup, (dup + 1), ft_strlen(dup + 1) + 1);
	}
	return (dup);
}

static char	*trim_end(char *dup, const char *set)
{
	while (ft_strlen(dup) && isset(*(dup + ft_strlen(dup) - 1), set))
	{
		*(dup + ft_strlen(dup) - 1) = '\0';
	}
	return (dup);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*dup;
	char	*res;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return ((char *)s1);
	dup = ft_strdup(s1);
	if (!dup)
		return (NULL);
	dup = trim_end(trim_ini(dup, set), set);
	len = ft_strlen(dup);
	res = (char *) malloc (sizeof(char) * len + 1);
	if (res == NULL)
	{
		free(dup);
		return (NULL);
	}
	res = ft_memmove(res, dup, ft_strlen(dup) + 1);
	free(dup);
	return (res);
}
