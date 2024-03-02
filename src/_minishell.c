/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/27 17:36:17 by mvisca           ###   ########.fr       */
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
			return (utils_free_ms(&ms));
		debug_token(&ms);
		if (parser(&ms) != 0)
			return (utils_free_ms(&ms));
		
		free(ms.line);
		utils_free_token_list(&ms);
	}
	ft_printf(YELLOW"Natural exit\n");
	utils_free_ms(&ms);

	return (0);
}
