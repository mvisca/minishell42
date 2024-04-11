/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/11 19:25:24 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_exit(t_ms *ms)
{
	if (ms->cmnd_list->command && ms->cmnd_list->command[0] \
	&& ft_strnstr(ms->cmnd_list->command[0], "exit", 4))
		return (1);
	return (0);
}

static int	empty_exit(void)
{
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	exit (0);
}

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	initialize(&ms, ac, av, envp);
	while (1)
	{
		signal_init(1);
		/*
		if (interface_get_line(&ms) != 0)
			continue ;
		else if (errors_syntax(&ms) != 0)
		{
			free(ms.line);
			continue ;
		}
		*/
		interface_get_line(&ms); // control de errores eliminado
		if ((!ms.line && empty_exit()) || ms.line[0] == 0)
			continue ;
		if (lexer(&ms, ms.line) != 0)
			return (utils_free_ms(&ms, TRUE));
		if (parser(&ms) != 0)
			return (utils_free_ms(&ms, TRUE));
		expander(&ms);
//		debug_all(&ms, 0, 0, 1);
		if (check_exit(&ms)) // eliminar al implement builtins
			break ;
		ft_execute(&ms);
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return (0);
}
