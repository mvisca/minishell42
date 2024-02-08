/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:58:57 by mvisca-g          #+#    #+#             */
/*   Updated: 2023/07/10 01:10:56 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

static char	*ft_makeitoa(int ncpy, char *tmp)
{
	while (ncpy / 10 > 0)
	{
		ft_memmove((tmp + 1), tmp, ft_strlen(tmp));
		tmp[0] = ncpy % 10 + '0';
		ncpy = ncpy / 10;
	}
	ft_memmove((tmp + 1), tmp, ft_strlen(tmp));
	tmp[0] = ncpy + '0';
	return (tmp);
}

char	*ft_itoa(int n)
{
	char	*tmp;
	char	*res;
	int		ncpy;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ncpy = ft_abs(n);
	tmp = (char *) ft_calloc (13, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	ft_makeitoa(ncpy, tmp);
	if (n < 0)
	{
		ft_memmove(&tmp[1], tmp, ft_strlen(tmp));
		tmp[0] = '-';
	}
	res = ft_strdup(tmp);
	free(tmp);
	return (res);
}
