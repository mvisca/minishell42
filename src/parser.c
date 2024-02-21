/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/21 00:06:09 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser_count_nodes(t_tokl *token)
{
	int	len;

	len = 0;
	while (token)
	{
		len++;
		token = token->next;
	}
	return (len);
}

int	parser(t_ms *ms)
{
	int		len;
	t_tokl	*start;
	t_coml	*command;

	start = ms->token_list;
	len = parser_count_nodes(start);
	while (start->type != END)
	{
		command = parser_alloc_command(len);
		if (!command)
			return (1);
		if (parser_init_command(command, start) != 0)
			return (1);
		parser_add_command(ms, command);
		ft_printf("EEYTT Command %p\n", command);
		ft_printf("parser alloc %p\n", ms->comnd_list);
		ft_printf("Ms->commd_list %p\n", ms->comnd_list);
		while(start->type != PIPE && start->type != END)
			start = start->next;
		if (start->type == PIPE)
			start = start->next;
	}
	debug_command(ms);
	lexer_clean(ms);
	return (0);
}
