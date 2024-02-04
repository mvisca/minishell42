/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:55:11 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/07/10 01:10:38 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static void	ft_d_minor_s(size_t *i, size_t *e, size_t n, int *d)
{
	*i = 0;
	*e = n - 1;
	*d = 1;
}

static void	ft_s_minor_d(size_t *i, size_t *e, size_t n, int *d)
{
	*i = n - 1;
	*e = 0;
	*d = -1;
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	size_t		end;
	int			delta;

	if (dest != src)
	{
		if (dest < src)
			ft_d_minor_s(&i, &end, n, &delta);
		else
			ft_s_minor_d(&i, &end, n, &delta);
		while (i != end + delta)
		{
			((char *)dest)[i] = *(((char *) src) + i);
			i += delta;
		}
	}
	return (dest);
}
