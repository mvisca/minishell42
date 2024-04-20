/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/20 16:46:22 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;

static int	empty_exit()
{
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	exit (0); // probar exito code en mac
}

static int	check_exit(t_ms *ms)
{
	if (ms->cmnd_list->command && ms->cmnd_list->command[0] \
	&& ft_strnstr(ms->cmnd_list->command[0], "exit", 4))
	{
		write(1, "exit\n", 5);
		return (0); // probar exito code en mac
	}
	return (0);
}
int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	initialize(&ms, ac, av, envp);
	while (1)
	{
		if (signal_init(INTERACTIVE) != 0)
			break ;
		interface_get_line(&ms);
		signal_ignore(SIGQUIT);
		signal_ignore(SIGINT);
		if ((!ms.line && empty_exit()) || ms.line[0] == 0)
			continue ;
		if (lexer(&ms, ms.line) != 0 || parser(&ms) != 0)
			continue ;
		expander(&ms);
		if (check_exit(&ms))
			break ;
		// environment_init(ms) // hay que reiniciar el env antes del executer por si el contexto fue modificado desde otra termina (borrar el folder donde estamos actundo, crea files, mover a otro dir estando .trash, etc).
		ft_execute(&ms);
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return (0);
}
