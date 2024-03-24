/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:41:47 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/24 14:49:51 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser_add_redirect(t_coml *cmnd, t_redl *redir)
{
	t_redl	*aux;

	if (!cmnd->redirect)
		cmnd->redirect = redir;
	else
	{
		aux = cmnd->redirect;
		while (aux->next)
			aux = aux->next;
		aux->next = redir;
	}
	return (0);
}

int	parser_add_command(t_ms *ms, t_coml *command)
{
	t_coml *aux;

	if (!ms->cmnd_list)
		ms->cmnd_list = command;
	else
	{
		aux = ms->cmnd_list;
		while (aux->next)
			aux = aux->next;
		aux->next = command;
	}
	return (0);
}

t_coml	*parser_new_command(t_coml **command)
{
	*command = (t_coml *)ft_calloc(1, sizeof(t_coml));
	if (!*command)
		return (NULL);
	(*command)->command = NULL;
	(*command)->redirect = NULL;
	(*command)->next = NULL;
	return (*command);
}
