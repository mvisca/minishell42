/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:29:23 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/15 21:31:55 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	signal_ctrl_term(int sig)
{
	if (sig == SIGTERM)
	{
		printf("TERM\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	signal_ctrl_quit(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("QUIT\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	signal_ctrl_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("INT\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_init(void)
{
	signal(SIGTERM, signal_ctrl_term);
	signal(SIGQUIT, signal_ctrl_quit);
	signal(SIGINT, signal_ctrl_int);
}
//https://github.com/DinaGala/42_minishell/blob/main/src/signals/signals.c
