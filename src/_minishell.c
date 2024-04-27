/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/27 13:53:06 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;


static int	empty_exit(t_ms *ms)
{
	write(2, "exit\n", 5);
	free(ms->line);
	ms->line = NULL;
	utils_free_ms(ms, TRUE);
	exit (1);
}

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	initialize(&ms, ac, av, envp);
	while (1)
	{
		if (signal_init(INTERACTIVE) != 0)
			break ;
		signal_ignore(SIGQUIT);
		interface_get_line(&ms);
		signal_ignore(SIGINT);
		if (!ms.line && isatty(STDIN_FILENO) && empty_exit(&ms))
			break ;
		if (ms.line && ms.line[0] == 0 && utils_free_ms(&ms, FALSE))
			continue ;
		if (lexer(&ms, ms.line) != 0 || parser(&ms) != 0)
			continue ;
		expander(&ms);
//		environment_init(&ms, envp); // hay que reiniciar el env arr antes del executer por si el contexto fue modificado desde otra termina (borrar el folder donde estamos actundo, crea files, mover a otro dir estando .trash, etc).
//		ft_execute(&ms);
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return (0);
}
