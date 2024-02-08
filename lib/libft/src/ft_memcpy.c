/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:51:29 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/08/08 12:12:33 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dcpy;
	unsigned char	*scpy;

	dcpy = (unsigned char *)dest;
	scpy = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		dcpy[i] = scpy[i];
		i++;
	}
	while (i < n)
		(dcpy)[i++] = '\0';
	return (dcpy);
}
