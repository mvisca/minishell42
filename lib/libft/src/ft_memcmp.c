/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:48:34 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/06/30 18:22:56 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;
	size_t			i;

	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	i = 0;
	if (n > 0)
	{
		while (us1[i] == us2[i] && i < n -1)
			i++;
		return (us1[i] - us2[i]);
	}
	return (0);
}
