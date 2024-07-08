/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/08 16:37:59 by fcatala-         ###   ########.fr       */
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
		if (!ms.syntax_errors)//debe
			ft_execute(&ms);
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return ((unsigned char)g_exit);
}
