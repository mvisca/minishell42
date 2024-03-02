/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:41:47 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/27 19:08:04 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser_add_command(t_ms *ms, t_coml *command)
{
	t_coml *aux;

	aux = ms->comnd_list;
	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = command;
	}
	else 
		ms->comnd_list = command;
	return (0);
}

t_coml	*parser_new_command(t_coml *command)
{
	command = (t_coml *)malloc(sizeof(t_coml));
	if (!command)
		return (NULL);
	command->command = NULL;
	command->redirect = NULL;
	command->next = NULL;
	return (command);
}
