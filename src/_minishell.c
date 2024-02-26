/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 19:27:55 by mvisca           ###   ########.fr       */
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
			return (utils_free_ms(&ms));
		if (lexer(&ms, ms.line) != 0)
			return (utils_free_ms(&ms));

		debug_token(&ms);
		ft_printf(YELLOW"DEBUG LEXER DONE\n"RESET);

		if (parser(&ms) != 0)
		{
			ft_printf("Killing it at parser end\n");
			return (utils_free_ms(&ms));
		}
		ft_printf("Overcoming parser end\n");


		if (ft_strnstr(ms.token_list->str, "exit", 4))
		{
			ft_printf(BLUE"Input:"RED" exit\n"RESET);
			break ;
		}
		ft_printf("BUCLE MAIN DONE\n");
		utils_free_token_list((&ms)->token_list); // deberá in en parser
	}
	utils_free_ms(&ms);
	return (0);
}
