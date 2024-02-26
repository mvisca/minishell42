/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 16:34:43 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser_pre(t_coml **cmnd, t_tokl *start)
{
	while (start->type != PIPE && start->type != END)
	{
		if (start->type == WORD)
		{
			(*cmnd)->pre_cmnd = str_ext_cmnd(*cmnd, start->str);
			if (!(*cmnd)->pre_cmnd)
				return (1);
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

int	parser(t_ms *ms)
{
	t_tokl	*start;
	t_coml	*command;
	int		res;

	start = ms->token_list;
	while (start->type != END)
	{
		if (start->type == PIPE)
			start = start->next;
		parser_alloc_command(command);
		ft_printf("parser dirmem command %p\n", command);
		if (!command)
			return (1);
		res = parser_pre(&command, start);
		ft_printf("parser command dirmem despues parser_pre %p\n", command);
		ft_printf("parser command precmnd dirmem despues parser_pre %p\n", command->pre_cmnd);
		ft_printf("parser command precmnd str %s\n", command->pre_cmnd->str);
		ft_printf("parser res parser pre %d\n", res);
		if (res)
			return (1);
		// parse_pos
		parser_add_command(ms, command);
		while (start->type != PIPE || start->type != END)
			start = start->next;
	}
	usleep(111);
// parser_pretofinal
//	debug_command(ms);
//	lexer_clean(ms);
	return (0);
}
