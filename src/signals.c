/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:29:23 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/16 17:51:50 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Maneja la senyal intrrupt durante consola interactiva
static void	interactive_handler(int signum)
{ 
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 1;
	}
}

// Maneja la senyal interrupt durante heredoc
static void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit(1);
	}
}

// Silencia el echo de los comandos con control
static void	signal_silent(void)
{
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal.c_cflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminal);
}

int	signal_init(int mode)
{
	struct sigaction	sa;

	signal_silent();
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // | SA_SIGINFO;
	if (mode == INTERACTIVE)
		sa.sa_handler = interactive_handler;
	if (mode == HEREDOC)
		sa.sa_handler = heredoc_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1 || \
	sigaction(SIGQUIT, &sa, NULL) == -1)
		return (1);
	return (0);
}

int	signal_ignore(int sig_type)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	if (sigaction(sig_type, &sa, NULL) != 0)
		return (1);
	return (0);
}