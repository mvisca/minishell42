/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_getters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 05:07:18 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/22 06:50:56 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Tested OK
t_envl	*environment_get_node(t_ms *ms, char *key)
{
	t_envl	*aux_node;

	aux_node = ms->envlst;
	while (aux_node)
	{
		if (!ft_strcmp(aux_node->key, key))
			return (aux_node);
		aux_node = aux_node->next;
	}
	return (NULL);
}

// Revisar si queremos que devuelva un string alocado o la dirección del value
// Tested Ok
char	*environment_get_value(t_ms *ms, char *key)
{
	t_envl	*aux_node;
	char	*res;

	res = NULL;
	aux_node = environment_get_node(ms, key);
	if (aux_node)
	{
		res = aux_node->value;
		if (res && res[0] == '\n' && res[1] && res[1] == '\0')
			return (&res[1]);
	}
	return (res);
}
