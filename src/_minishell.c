/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:39:00 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/16 20:10:30 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;

static int	empty_exit()
{
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	exit (1);
}

static int	check_exit(t_ms *ms)
{
	if (ms->cmnd_list->command && ms->cmnd_list->command[0] \
	&& ft_strnstr(ms->cmnd_list->command[0], "exit", 4))
	{
		write(1, "exit\n", 5);
		return (1);
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
			return (utils_free_ms(&ms, TRUE));
		expander(&ms);
		if (check_exit(&ms))
			break ;
		ft_execute(&ms);
		utils_free_ms(&ms, FALSE);
	}
	utils_free_ms(&ms, TRUE);
	return (0);
}
