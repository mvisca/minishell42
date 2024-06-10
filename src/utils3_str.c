/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatala- <fcatala-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:26:07 by fcatala-          #+#    #+#             */
/*   Updated: 2024/06/10 19:31:53 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_freechain(char **chain)
{
	int	i;

	i = -1;
	while (chain[++i])
		free(chain[i]);
	free(chain);
}

void	*ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
