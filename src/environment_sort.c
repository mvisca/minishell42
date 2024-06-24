/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:48:44 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/24 10:17:13 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	environment_sort(t_envl **env)
{
	t_envl	*curr;
	t_envl	*prev;
	char	*key;
	char	*value;

	prev = *env;
	while (prev)
	{
		curr = prev->next;
		while (curr)
		{
			if (ft_strcmp(prev->key, curr->key) > 0)
			{
				key = prev->key;
				value = prev->value;
				prev->key = curr->key;
				prev->value = curr->value;
				curr->key = key;
				curr->value = value;
			}
			curr = curr->next;
		}
		prev = prev->next;
	}
}
