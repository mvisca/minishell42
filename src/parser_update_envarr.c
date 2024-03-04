/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_update_envarr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:56:59 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/04 22:34:03 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	parser_init_redir(t_coml *command, t_tokl *token)
// {
// 	t_redl	*redir;

// 	redir = command->redirect;
// 	while (redir && redir->next)
// 		redir = redir->next;
// 	redir->path = ft_strdup(token->str);
// 	redir->type = token->type;
// 	redir->next = NULL;
// 	return (0);
// }

// int	parser_alloc_add_redir(t_coml *command)
// {
// 	t_redl	*redir;
// 	t_redl	*aux;

// 	redir = (t_redl *)ft_calloc(1, sizeof(t_redl));
// 	// redir = (t_redl *)supresedmalloc(sizeof(t_redl));
// 	if (!redir)
// 		return (1);
// 	redir->type = 0;
// 	redir->path = NULL;
// 	redir->next = NULL;
// 	aux = command->redirect;
// 	if (!aux)
// 	{
// 		command->redirect = redir;
// 		return (0);
// 	}
// 	while (aux->next)
// 		aux = aux->next;
// 	aux->next = redir;
	
// 	return (0);
// }

int parser_update_envarr(t_ms *ms)
{
	int     nodes_num;
	int		i;
	t_envl  *envnode;
	char    **newarr;
	char	*aux;

	// cuento los nodos
	nodes_num = 0;
	envnode = ms->envlst;
	while (envnode)
	{
		envnode = envnode->next;
		nodes_num++;
	}
	// alloco en newarr de numero de nodos + 1
	newarr = (char **)ft_calloc(nodes_num + 1, sizeof(char **));
	if (!newarr)
		return (1);
	
	// recorro los nodos
	envnode = ms->envlst;
	i = 0;
	while (envnode)
	{
		// concateno los key = value de los nodos en newarr
		aux = ft_strjoin(envnode->key, "=");
		newarr[i++] = ft_strjoin(aux, envnode->value);
		envnode = envnode->next;
		free(aux);
	}
	// guardo el array creado en envarr
	ms->envarr = newarr;
	return (0);
}