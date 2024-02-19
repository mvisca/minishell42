/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:41:47 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/19 20:45:08 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_end(t_tokl *start, t_tokl **end)
{
	int		len;

	len = 1;
	*end = start;
	while ((*end)->type != END && (*end)->type != PIPE)
	{
		len++;
		*end = (*end)->next;
	}
	return (len);
}

static t_redl	*add_redir_node(t_coml **comnd, t_redl *redir)
{
	t_redl *aux;

	aux = (*comnd)->redirect;
	if (!aux)
	{
		aux = redir;
		return (redir);
	}
	while (aux->next)
		aux = aux->next;
	aux->next = redir;
	return (redir);
}

t_redl	*make_redir_node(t_coml *comnd)
{
	t_redl *redir;

	redir = (t_redl *)malloc(sizeof(t_redl));
	if (!redir)
		return (NULL);
	redir->type = END;
	redir->path = NULL;
	redir->next = NULL;
	add_redir_node(&comnd, redir);
	return (redir);
}

static int	add_comnd_node(t_ms *ms, t_coml *comnd)
{
	t_coml	*aux;

	aux = ms->comnd_list;
	if (!aux)
	{
		ms->comnd_list = comnd;
		return (0);
	}
	while (aux->next)
		aux = aux->next;
	aux->next = comnd;
	return (0);
}	

int	make_comnd_node(t_ms *ms, t_tokl *start)
{
	t_coml	*command;
	t_tokl	*end;
	int		len;
	
	len = find_end(start, &end);
	command = (t_coml *)malloc(sizeof(t_coml));
	if (!command)
		return (1);
	command->command = (char **)malloc(sizeof(char *) * (len + 1));
	if (!command->command)
		return (1);
	command->command[0] = NULL;
	command->redirect = NULL;
	command->next = NULL;
	add_comnd_node(ms, command);
	return (0);
}
