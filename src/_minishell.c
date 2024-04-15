/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/15 18:36:51 by fcatala-         ###   ########.fr       */
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
	int 	ctr;

//	signal_init();
	ctr = 0;
	initialize(&ms, ac, av, envp);
	while (1 && ++ctr < 10)
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
		expander(&ms);
		debug_all(&ms, 0, 0, 1);
		if (check_exit(&ms))
			break ;
		ft_execute(&ms);
		printf("Salida\n");
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return (0);
}
