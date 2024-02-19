/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:48:37 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/18 22:04:21 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int array_append(t_coml *comnd, t_tokl *start)
{
	int		i;

	if (!comnd->command)
		return (1);
	i = ft_tablen(comnd->command);
	comnd->command[i] = ft_strdup(start->str);
	comnd->command[i + 1] = NULL;
	return (0);
}
