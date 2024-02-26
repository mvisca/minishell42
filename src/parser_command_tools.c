/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:41:47 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 18:02:41 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser_pre(t_coml **cmnd, t_tokl *start)
{
	while (start->type != PIPE && start->type != END)
	{
		if (start->type == WORD)
		{

			(*cmnd)->pre_cmnd = (t_tokl *)malloc(sizeof(t_tokl));
			if (!(*cmnd)->pre_cmnd)
				return (1);
			(*cmnd)->pre_cmnd->next = NULL;
			(*cmnd)->pre_cmnd->str = NULL;
			
			ft_printf(BRICK"Parser Pre"RESET"\n\tstart->str "YELLOW"%s"RESET"\n\tcmnd (address) "YELLOW"%p"RESET"\n\tcmnd->pre_cmnd (address) "YELLOW"%p\n"RESET, start->str, *cmnd, (*cmnd)->pre_cmnd);
			
			(*cmnd)->pre_cmnd = str_ext_cmnd(cmnd, start->str);

		}
		else
		{
		//	pre_redirect = str_extract_redirect(pre_redirect, start);
			start = start->next;
		}
		if (start->next)
			start = start->next;
	}
	return (0);
}

int	parser_add_command(t_ms *ms, t_coml *command)
{
	t_coml *aux;

	aux = ms->cmnd_list;
	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = command;
	}
	else 
		ms->cmnd_list = command;
	return (0);
}

t_coml	*parser_alloc_command(void)
{
	t_coml	*command;

	command = (t_coml *)malloc(sizeof(t_coml));
	if (!command)
		return (NULL);
	command->pre_cmnd = NULL;
	command->pre_redir = NULL;
	command->command = NULL;
	command->redirect = NULL;
	command->next = NULL;
	return (command);
}
