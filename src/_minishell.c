/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/15 13:46:04 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t g_exit;//

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	initialize(&ms, ac, av, envp);
	while (1 && g_exit != 130)
	{
		if (signal_init(INTERACTIVE) != 0)
			break ;
		signal_ignore(SIGQUIT);
		if (interface_get_line(&ms) != 0)
			continue ;
		signal_ignore(SIGINT);
		if (lexer(&ms, ms.line) != 0 || parser(&ms) != 0)
			continue ;
		expander(&ms);
//		environment_init(&ms, envp); // hay que reiniciar el env arr antes del executer por si el contexto fue modificado desde otra termina (borrar el folder donde estamos actundo, crea files, mover a otro dir estando .trash, etc).
//		debug_all(&ms, 1, 0, 0);
		ft_execute(&ms);
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return (g_exit);
}

