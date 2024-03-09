/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:29:23 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/09 13:40:25 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void father_signal_handler(int signum, siginfo_t *info, void *ctx)
{
	(void)ctx;
	(void)info;
	if (signum == SIGINT ) // macros de signals
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

static void child_signal_handler(int signum, siginfo_t *info, void *ctx)
{
	(void)ctx;
	(void)info;
	if (signum == SIGINT ) // macros de signals
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

int signals_init(int i)
{
	struct sigaction	s_sa;

	if (i)
		s_sa.sa_sigaction = &father_signal_handler;
	else 
		s_sa.sa_sigaction = &child_signal_handler;
//	s_sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &s_sa, NULL) == -1 \
	|| sigaction(SIGQUIT,  &s_sa, NULL) == -1 \
	|| sigaction(SIGTERM, &s_sa, NULL) == -1)
		return (1);
	return (0);
}
