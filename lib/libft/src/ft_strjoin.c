/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:21:55 by mvisca-g          #+#    #+#             */
/*   Updated: 2024/05/11 00:38:24 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1)
		len1 = 0;
	if (!s2)
		len2 = 0;
	i = -1;
	new = (char *) malloc (sizeof(char) * (len1 + len2 + 1));
	if (new)
	{
		while (++i < (len1 + len2))
		{
			*(new + i) = *(s2 + i - len1);
			if (i < len1)
				*(new + i) = *(s1 + i);
		}
		*(new + i) = '\0';
	}
	return (new);
}
