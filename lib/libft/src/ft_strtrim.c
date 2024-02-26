/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:23:46 by mvisca-g          #+#    #+#             */
/*   Updated: 2024/02/26 19:18:56 by mvisca           ###   ########.fr       */
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

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	ini;
	size_t			end;
	char			*aux;

 	if (s1 == NULL || set == NULL)
 		return ((char *)s1);
	ini = 0;
	while (s1[ini] && isset(s1[ini], set))
		ini++;
	end = ft_strlen(s1);
	while (end > (size_t)ini && isset(s1[end - 1], set))
		end--;
	aux = ft_substr(s1, ini, (end - (size_t)ini));
	if (!aux)
		return (NULL);
	return (aux);
}
