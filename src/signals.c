/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:29:23 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/30 11:51:13 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Silent diplays of signals
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
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (mode == NORMAL)
		sa.sa_handler = normal_handler;
	if (mode == INTERACTIVE)
	{
		rl_event_hook = ft_event_hook2;
		sa.sa_handler = interactive_handler;
	}
	if (mode == HEREDOC)
	{
		g_exit = 0;
		rl_event_hook = ft_event_hook;
		sa.sa_handler = heredoc_handler;
	}
	if (mode == 4)
		g_exit = 0;
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
