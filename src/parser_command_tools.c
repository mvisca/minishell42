/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:41:47 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/21 09:57:54 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser_add_command(t_ms *ms, t_coml *command)
{
	t_coml *aux;

	ft_printf(YELLOW"PARSER ADD command %p\n"RESET, command);
	aux = ms->comnd_list;
	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = command;
	}
	else 
		ms->comnd_list = command;
	ft_printf(GREEN"Add command list to ms %p %p\n"RESET, aux, ms->comnd_list);
	return (0);
}

int	parser_init_command(t_coml *command, t_tokl *start)
{
	int	i;

	i = 0;
	while (start->type != PIPE && start->type != END \
	&& start->type != L_REDIRECT && start->type != DL_REDIRECT \
	&& start->type != R_REDIRECT && start->type != DR_REDIRECT)
	{
		command->command[i++] = ft_strdup(start->str);
		start = start->next;
	}
	while(start->type != PIPE && start->type != END)
	{
		if (parser_alloc_add_redir(command) != 0)
			return (1);
		parser_init_redir(command, start);
		start = start->next;
	}
	command->next = NULL;
	return (0);
}

t_coml	*parser_alloc_command(int len)
{
	t_coml	*command;
	int		i;

	command = (t_coml *)malloc(sizeof(t_coml));
	if (!command)
		return (NULL);
	command->command = (char **)malloc(sizeof(char *) * (len));
	
	if (!command->command)
		return (NULL);
	
	i = 0;
	while (i < len)
	{
		command->command[i++] = NULL;
		ft_printf("nulled command->command[%d]\n", i);
	}
	command->redirect = NULL;
	command->next = NULL;
	return (command);
}
