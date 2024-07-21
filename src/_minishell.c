/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/21 18:13:21 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_exit;//creo que debemos cambiarla de sitio

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	initialize(&ms, ac, av, envp);
	rl_initialize();
	while (1)
	{
		utils_free_ms(&ms, FALSE);
		if (ms.token_list.str)
			printf("Type is %d\n", ms.token_list.type);
		printf("Ready 1\n");
		ms.syntax_errors = 0;
		if (signal_init(NORMAL) != 0)
			break ;
		signal_ignore(SIGQUIT);
		if (interface_get_line(&ms) != 0)
			continue ;
		signal_ignore(SIGINT);
		if (lexer(&ms, ms.line) != 0 || parser(&ms) != 0)
			continue ;
		expander(&ms);
		printf("Ready 2\n");
		if (!ms.syntax_errors)
			ft_execute(&ms);
		utils_free_ms(&ms, FALSE);
		printf("Ready 3\n");
	}
	utils_free_ms(&ms, TRUE);
	return (ms.exit_code);
}
