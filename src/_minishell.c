/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/01 11:51:50 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t g_exit;

int	main(int ac, char **av, char **envp)
{
	t_ms	ms;

	initialize(&ms, ac, av, envp);
	rl_initialize();
	while (1)
	{
		if (signal_init(NORMAL) != 0)
			break ;
		signal_ignore(SIGQUIT);
		if (interface_get_line(&ms) != 0)
			continue ;
		signal_ignore(SIGINT);
		if (lexer(&ms, ms.line) != 0 || parser(&ms) != 0)
			continue ;
		debug_all(&ms, 0, 0, 1);
		expander(&ms);
		ft_execute(&ms);
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return ((unsigned char)g_exit);
}

