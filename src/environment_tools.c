/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:20 by mvisca            #+#    #+#             */
/*   Updated: 2024/05/18 10:52:25 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Creates new t_envl node
// Tested Ok
t_envl	*environment_new_node(t_ms *ms, char *key, char *value)
{
	t_envl	*new;

	new = (t_envl *)ft_calloc(1, sizeof(t_envl));
	// new = (t_envl *)supresed_malloc(sizeof(t_envl));
	if (!new)
		error_free_exit("malloc error", ms);
	new->next = NULL;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (!new->key || !new->value)
	{
		free(new->key);
		if (new->value)
			free(new->value);
		free(new);
		error_free_exit("malloc error", ms);
	}
	return (new);
}

// Adds node at the end of the list
// Tested Ok
t_envl	*environment_add_node(t_ms *ms, t_envl *envnode)
{
	t_envl	*aux;

	if (ms->envlst == NULL)
		ms->envlst = envnode;
	else
	{
		aux = ms->envlst;
		while (aux->next)
			aux = aux->next;
		aux->next = envnode;
	}
	return (ms->envlst);
}

// Deletes the node with the given key
// To be tested
void	environment_del_node(t_ms *ms, char *key)
{
	t_envl	*prev;
	t_envl	*aux;

	prev = NULL;
	aux = ms->envlst;
	while (aux)
	{
		if (ft_strncmp(aux->key, key, ft_strlen(key)))
		{
			if (prev)
				prev->next = aux->next;
			else
				ms->envlst = aux->next;
			free(aux->key);
			free(aux->value);
			return ;
		}
		aux = aux->next;
	}
}

// Finds the node with the key and updates its value
// To be tested
void	environment_update_node(t_ms *ms, char *key, char *value)
{
	t_envl	*aux_node;

	aux_node = environment_get_node(ms, key);
	if (aux_node)
	{
		if (aux_node->value)
			free(aux_node->value);
		aux_node->value = value;
	}
}
