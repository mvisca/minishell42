/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:29:23 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/20 15:07:15 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Set the exit code to 130 to indicate SIGINT was received
//rl_done = 1; will cause readline to return
static int	ft_event_hook(void)
{
	if (g_exit == 130)
	{
		rl_done = 0;
	}
	return (0);
}

static int	ft_event_hook2(void)
{
	return (0);
}


//ok display but bad error code
static void	normal_handler (int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// Maneja la senyal intrrupt durante consola interactiva
static void	interactive_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_done = 1;
//		rl_replace_line("", 1);
//		rl_on_new_line();
//		rl_redisplay();
		g_exit = 130;
	}
}


// Maneja la senyal interrupt durante heredoc
static void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_done = 1;
		g_exit = 130;
	}
}

// Silencia el echo de los comandos con control
//Se puede pone en init?
static void	signal_silent(void)
{
	struct termios	terminal;

	tcgetattr(0, &terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminal);
}

int	signal_init(int mode)
{
	struct sigaction	sa;

	signal_silent();
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // | SA_SIGINFO;
	if (mode == NORMAL)
	{
		sa.sa_handler = normal_handler;
	}
	if (mode == INTERACTIVE)
	{
		rl_event_hook = ft_event_hook2;
		sa.sa_handler = interactive_handler;
	}
	if (mode == HEREDOC)
	{
		rl_event_hook = ft_event_hook;
		sa.sa_handler = heredoc_handler;
	}
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
