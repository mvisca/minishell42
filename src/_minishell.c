/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/06 01:09:40 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	initialize(&ms, ac, av, envp);
	while (1)
	{
		if (interface_get_line(&ms) != 0)
			continue ;
		else if (errors_syntax(&ms) != 0)
		{
			free(ms.line);
			continue ;
		}
		if (lexer(&ms, ms.line) != 0)
			return (utils_free_ms(&ms, TRUE));
		debug_token(&ms);
		if (parser(&ms) != 0)
			return (utils_free_ms(&ms, TRUE));
		debug_command(&ms);
		if (ms.cmnd_list->command && ms.cmnd_list->command[0] && ft_strnstr(ms.cmnd_list->command[0], "exit", 4))
			break ;
		utils_free_ms(&ms, FALSE);
	}
	ft_printf(YELLOW"Natural exit\n"RESET);
	utils_free_ms(&ms, TRUE);
	return (0);
}
