/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_envarr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:56:59 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/16 21:27:19 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	parser_count_env_nodes(t_envl **envnode, t_ms *ms, int *i)
{
	int	nodes_num;

	nodes_num = 0;
	while (*envnode)
	{
		*envnode = (*envnode)->next;
		nodes_num++;
	}
	*envnode = ms->envlst;
	*i = 0;
	return (nodes_num);
}

// Actualiza el array env antes para el executor
int	parser_update_envarr(t_ms *ms)
{
	int		nodes_num;
	int		i;
	t_envl	*envnode;
	char	**newarr;
	char	*aux;

	envnode = ms->envlst;
	nodes_num = parser_count_env_nodes(&envnode, ms, &i);
	newarr = (char **)ft_calloc(nodes_num + 1, sizeof(char **));
	if (!newarr)
		return (1);
	while (envnode)
	{
		aux = ft_strjoin(envnode->key, "=");
		newarr[i++] = ft_strjoin(aux, envnode->value);
		envnode = envnode->next;
		free(aux);
	}
	ms->envarr = newarr;
	return (0);
}
