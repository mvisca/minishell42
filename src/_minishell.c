/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/16 09:20:25 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	jump_line(t_minishell *ms)
{
	if (!ft_strtrim(ms->line, SPACES)[0])
	{
		free(ms->line);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;

	initialize(&ms, ac, av, envp);
	while (1)
	{
		interface_get_line(&ms);
		if (jump_line(ms.line))
			continue ;
		errors_syntax(&ms);
		if (lexer(&ms, ms.line) != 0 || parser(&ms) != 0)
			return (utils_free_ms(&ms));
		if (ft_strnstr(ms.token_list->str, "exit", 4))
		{
			ft_printf(RED"Input:"BLUE" exit\n"RESET);
			break ;
		}
		parser(&ms);
	}
	utils_free_ms(&ms);
	return (0);
}

/*	manejador de señales para evitar salir con 
		ctrl + c
		ctrol + \
		ctrol + D
		revisar	*/

		// EXECUTOR
			// la siguiente líneas es temporar
			// terminal minishell
			// será parte del manejo de comandos
				// exit es una especie de "builtin"?
					// en este caso debe limpiar memoria
				// exit es un comando que a través de execv?
			// bucle de pipes
				// EXPANDER
					// antes de enviar a ejecutar se expande
				// FILEDESCRIPTORS
					// antesde enviar a ejecutar 
				// envía a ejecutar

		// exit temporal para probar leaks