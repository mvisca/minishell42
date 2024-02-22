/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:56:59 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/22 08:51:27 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser_init_redir(t_coml *command, t_tokl *token)
{
	t_redl	*redir;

	redir = command->redirect;
	while (redir && redir->next)
		redir = redir->next;
	redir->path = ft_strdup(token->str);
	redir->type = token->type;
	redir->next = NULL;
	return (0);
}

int	parser_alloc_add_redir(t_coml *command)
{
	t_redl	*redir;
	t_redl	*aux;

	redir = (t_redl *)malloc(sizeof(t_redl));
	if (!redir)
		return (1);
	redir->type = 0;
	redir->path = NULL;
	redir->next = NULL;
	aux = command->redirect;
	if (!aux)
	{
		command->redirect = redir;
		return (0);
	}
	while (aux->next)
		aux = aux->next;
	aux->next = redir;
	
	return (0);
}
