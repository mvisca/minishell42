/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:41:47 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/17 22:22:17 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_redl	*add_redirlst_node(t_coml *comnd, t_redl *redir)
{
	t_redl *aux;

	aux = comnd->redirect;
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

static int	make_redir_node(t_coml *comnd, t_tokl **start)
{
	t_redl *redir;

	redir = (t_redl *)malloc(sizeof(t_redl));
	if (!redir)
		return (1);
	redir->next = NULL;
	redir->type = (*start)->type;
	(*start) = (*start)->next;
	if ((*start)->type == WORD)
		redir->path = (*start)->str;
	else
		redir->path = NULL;
	if ((*start)->type != END)
		(*start) = (*start)->next;
	add_redirlst_node(comnd, redir);
	return (0);
}

static int	add_comnd_node(t_ms *ms, t_coml *comnd)
{
	t_coml	*aux;

	aux = ms->comnd_list;
	if (!aux)
	{
		ms->comnd_list = comnd;
		ft_printf("ms->comnd_list->commnad= '%s'", ms->comnd_list->command[0]);
		return (0);
	}
	while (aux->next)
		aux = aux->next;
	aux->next = comnd;
	return (0);
}

int	make_comnd_node(t_ms *ms, t_tokl *start, t_tokl *end)
{
	t_coml	*command;

	command = (t_coml *)malloc(sizeof(t_coml));
	if (!command)
		return (1);
	command->command = NULL;
	command->redirect = NULL;
	command->next = NULL;
	while (start != end)
	{
		if (start->type == WORD)
		{
			if (array_append(command, start, end) != 0)
				return (1);
			start = start->next;
		}  // ok
		else
		{ // redirlist gestiona la iteración de start TODO
			if (make_redir_node(command, &start) != 0)
				return (1);
		}
	}
	add_comnd_node(ms, command);
	return (0);
}

t_tokl	*find_end(t_tokl *start)
{
	t_tokl	*end;

	end = start;
	while (end->type != END && end->type != PIPE)
		end = end->next;
	return (end);
}