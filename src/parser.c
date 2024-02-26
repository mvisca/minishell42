/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 17:32:50 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser(t_ms *ms)
{
	t_tokl	*start;
	t_coml	*command;
	int		res;

	start = ms->token_list;
	while (start->type != END)
	{
		ft_printf(BARBIE"Parser"RESET"->Current token:\n");
		debug_print_token(start, 99);
		command = parser_alloc_command();
		if (!command)
			return (1);
		
		// FIX THIS
		res = parser_pre(&command, start);
		if (res)
		{
			ft_printf(RED"EXIT Parser"RESET" Salida en parser_pre retorna 1\n");
			return (1);
		}
		// parse_pos
		parser_add_command(ms, command);
		while (start->type != PIPE && start->type != END)
			start = start->next;
		if (start->type == PIPE)
			start = start->next;
		ft_printf(BLUE"Parser"RESET" -> fin de bucle\n");
	}
	usleep(111);
// parser_pretofinal
//	debug_command(ms);
//	lexer_clean(ms);
	return (0);
}
