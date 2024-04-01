/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_envarr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:56:59 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/24 20:46:44 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int parser_update_envarr(t_ms *ms)
{
	int     nodes_num;
	int		i;
	t_envl  *envnode;
	char    **newarr;
	char	*aux;

	nodes_num = 0;
	envnode = ms->envlst;
	while (envnode)
	{
		envnode = envnode->next;
		nodes_num++;
	}
	newarr = (char **)ft_calloc(nodes_num + 1, sizeof(char **));
	if (!newarr)
		return (1);
	envnode = ms->envlst;
	i = 0;
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