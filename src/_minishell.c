/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/19 21:46:40 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	initialize(&ms, ac, av, envp);
	while (1)
	{
		if (interface_get_line(&ms))
			continue ;
		if (errors_syntax(&ms))
			return (free_ms(&ms));
		ft_printf(RED"SYNTAX DONDE\n"RESET);
		if (lexer(&ms, ms.line) != 0)
			return (free_ms(&ms));
		ft_printf(RED"LEXER DONE\n"RESET);
		debug_token(&ms);
		ft_printf(YELLOW"DEBUG LEXER DONE\n"RESET);
		if (parser(&ms) != 0)
			return (free_ms(&ms));

		if (ft_strnstr(ms.comnd_list->command[0], "exit", 4))
		{
			ft_printf(BLUE"Input:"RED" exit\n"RESET);
			break ;
		}
	}
	free_ms(&ms);
	return (0);
}
