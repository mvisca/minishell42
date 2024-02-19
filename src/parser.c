/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/19 21:00:29 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	debug_parser(t_ms *ms)
{
	t_coml	*com;
	t_redl	*red;
	int		nodei;
	int		j;
	int		k;

	nodei = 1;
	ft_printf(RED"\nDebug Command\n\n"RESET);
	com = ms->comnd_list;
	while (com)
	{
		ft_printf(BLUE"Node Command %d\n"RESET, nodei++);
		k = 0;
		while (com->command && k < ft_tablen(com->command))
		{
			ft_printf(BLUE"Command[%d]= '"YELLOW" %s"BLUE"'\n"RESET, k, com->command[k]);

			red = com->redirect;
			j = 1;
			
			ft_printf(RED"red %p\n", red);
			while (red)
			{	
				ft_printf(BLUE"Node Command->Redirect %d"RESET, j++);
				ft_printf(BLUE"\tCommand->Redirect->Path = '"YELLOW"%s"BLUE"'\n"RESET, com->redirect->path);
				ft_printf(BLUE"\tCommand->Redirect->Path = '"YELLOW" %d"BLUE"'\n"RESET, com->redirect->type);
				ft_printf(MAGENTA"\t------------------\n"RESET);
				red = red->next;
			}
			k++;
		}
		ft_printf(CYAN"------------------\n"RESET);
		ft_printf("com address %p\n", com);
		com = com->next;
	}	
}

int	parser(t_ms *ms)
{
	t_tokl	*start;

	start = ms->token_list;
	while (start->type != END)
	{
		if (make_comnd_node(ms, start) != 0)
			return (1);	
		if (populate_comnd_node(ms, &start) != 0)
		return (1);
	}
	// clean spaces
	debug_parser(ms);
	lexer_clean(ms);
	return (0);
}
