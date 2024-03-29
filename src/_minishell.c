/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/17 18:59:16 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_exit(t_ms *ms)
{
	if (ms->cmnd_list->command && ms->cmnd_list->command[0] \
	&& ft_strnstr(ms->cmnd_list->command[0], "exit", 4))
	{
		ft_printf(YELLOW"Exit command received\n"RESET);
		return (1);
	}
	return (0);
}
int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	signal_init();
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
		if (parser(&ms) != 0)
			return (utils_free_ms(&ms, TRUE));
		if (DEBUG_ON)
			debug_all(&ms, 0, 1, 1);
		if (check_exit(&ms))
			break ;
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return (0);
}
