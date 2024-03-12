/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:29:23 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/11 22:50:25 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void father_sig_handler(int signum)
// {
// 	if (signum == SIGINT ) // macros de signals
// 	{
// 		rl_replace_line("", 0);
// 		ft_printf("\n");
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}	
// 	else if (signum == SIGQUIT)
// 	{
// 		rl_redisplay();
// 		ft_printf("exit\n");
// 	}
// 	else if (signum == SIGTERM)
// 		ft_printf("CTRL+\\\n");
// }

// static void child_sig_handler(int signum)
// {
// 	if (signum == SIGINT ) // macros de signals
// 	{
// //		rl_replace_line("", 0);
// 		ft_printf("\n");
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}	
// 	else if (signum == SIGQUIT)
// 	{
// 		rl_redisplay();
// 		ft_printf("exit\n");
// 	}
// 	else if (signum == SIGTERM)
// 		ft_printf("CTRL+\\\n");
// }

// // Recibe el pid como argumento.
// // En los fork se deberá pasar para que se gestion father y childs.
// int signals_init(int pid)
// {
// 	struct sigaction	sa;

// 	sa.sa_flags = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sigaddset(&sa.sa_mask, SIGINT);
// 	sigaddset(&sa.sa_mask, SIGQUIT);
// 	sigaddset(&sa.sa_mask, SIGTERM);
	
// 	if (pid < 0)
// 		return (1);
// 	else if (pid == 0)
// 		sa.sa_handler = child_sig_handler;
// 	else
// 		sa.sa_handler = father_sig_handler;
// 		s_sa.sa_flags = SA_RESTART;
// 	if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGQUIT,  &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) == -1)
// 		return (1);
// 	return (0);
// }

void	signal_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_init(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c);
}
//https://github.com/DinaGala/42_minishell/blob/main/src/signals/signals.c