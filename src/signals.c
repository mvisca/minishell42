/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:29:23 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/10 17:48:57 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	father_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_redisplay();
		ft_printf("exit\n");
	}
	else if (signum == SIGTERM)
		ft_printf("CTRL+\\\n");
}

static void	child_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_redisplay();
		ft_printf("exit\n");
	}
	else if (signum == SIGTERM)
		ft_printf("CTRL+\\\n");
}

int	signal_init(int pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGTERM);
	if (pid == 0)
		sa.sa_handler = child_sig_handler;
	else
	{
		sa.sa_handler = father_sig_handler;
		sa.sa_flags = SA_RESTART | SA_SIGINFO;
	}
	if (sigaction(SIGINT, &sa, NULL) == -1 || \
	sigaction(SIGQUIT, &sa, NULL) == -1 || \
	sigaction(SIGTERM, &sa, NULL) == -1)
		return (1);
	return (0);
}

//https://github.com/DinaGala/42_minishell/blob/main/src/signals/signals.c
