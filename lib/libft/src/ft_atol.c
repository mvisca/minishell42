/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:17:06 by mvisca            #+#    #+#             */
/*   Updated: 2023/08/02 14:22:42 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

long long int	ft_atol(const char *n)
{
	long long int	res;
	int				i;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((n[i] >= 9 && n[i] <= 13) || (n[i] == 32) || (n[i] == '0'))
		i++;
	if (n[i] == '-' || n[i] == '+')
	{
		if (n[i] == '-')
			sign = -1;
		i++;
	}
	while (n[i] >= '0' && n[i] <= '9')
		res = (res * 10) + n[i++] - '0';
	return (res * sign);
}
