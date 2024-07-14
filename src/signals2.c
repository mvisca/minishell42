/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:29:23 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/13 10:43:35 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Event in heredoc mode
int	ft_event_hook(void)
{
	rl_done = 0;
	return (0);
}

//Event in iteractive mode
int	ft_event_hook2(void)
{
	return (0);
}

//Handles the signal at the beginning
void	normal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 130;
	}
}

//Handles the signal in interactive mode
void	interactive_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_done = 1;
		g_exit = SIGINT;
	}
	else if (signum == SIGQUIT)
	{
		g_exit = SIGQUIT;
	}
}

//Handles the signal in here_doc mind the value!
void	heredoc_handler(int signum)
{
	signal_ignore(SIGQUIT);
	if (signum == SIGINT)
	{
		rl_done = 1;
		g_exit = SIGINT;
	}
//	else
//		g_exit = 0;
}
