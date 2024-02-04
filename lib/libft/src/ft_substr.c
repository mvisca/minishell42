/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:46:36 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/07/10 01:08:58 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*scpy;
	char		*sub;
	size_t		i;

	scpy = (char *)s;
	if (ft_strlen(scpy) == 0 || ft_strlen(scpy) < start)
		return ((char *)ft_calloc(1, 1));
	if (ft_strlen(scpy) < start + len)
		len = ft_strlen(scpy) - start;
	sub = (char *) malloc (sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len && (unsigned char) *(s + start + i))
	{
		*(sub + i) = *(s + start + i);
		i++;
	}
	*(sub + i) = '\0';
	return (sub);
}
