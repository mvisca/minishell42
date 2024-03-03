/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/03 14:46:33 by mvisca           ###   ########.fr       */
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

		if (errors_syntax(&ms) != 0)
		{
			free(ms.line);
			continue ;
		}
		if (lexer(&ms, ms.line) != 0)
			return (utils_free_ms(&ms, TRUE));

		debug_token(&ms);

		int parser_return = parser(&ms) != 0;


		ft_printf("Parser return: %d\n"RESET, parser_return);
		
		if (ms.cmnd_list && ms.cmnd_list->command)
		{
			ft_printf("Parser ms->cmnd->command %p", ms.cmnd_list->command);
		}
		else
		{
			ft_printf("No hay ms->cmnd->command\n");
		}
				
		if (parser_return)
		{
			ft_printf("Borrando todo\n");
			return (utils_free_ms(&ms, TRUE));
		}

		ft_printf("ms.cmnd_list->command[0] = %s\n", ms.cmnd_list->command[0]);
		if (ft_strnstr(ms.cmnd_list->command[0], "exit", 4))
		{
			free(ms.line);
			break ;
		}
		utils_free_ms(&ms, FALSE);
		free(ms.line);
		ft_printf(GREEN"Free all\n"RESET);
	}

	ft_printf(YELLOW"Natural exit\n"RESET);
	utils_free_ms(&ms, TRUE);

	return (0);
}
