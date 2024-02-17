/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/17 22:10:07 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	debug_parser(t_ms *ms)
{
	t_coml	*com;
	t_redl	*red;
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	com = ms->comnd_list;
	ft_printf(RED"\nDebug Command\n\n"RESET);
	while (com)
	{
		ft_printf(BLUE"Node Command %d\n"RESET, i++);
		while (com->command[k])
		{
			ft_printf(BLUE"Command[%d]= '"YELLOW" %s"BLUE"'\n"RESET, k++, com->command[0]);
			red = com->redirect;
			j = 1;
			ft_printf(RED"red %p", com->redirect);
			while (red)
			{	
				ft_printf(BLUE"Node Command->Redirect %d"RESET, j++);
				ft_printf(BLUE"\tCommand->Redirect->Path = '"YELLOW"%s"BLUE"'\n"RESET, com->redirect->path);
				ft_printf(BLUE"\tCommand->Redirect->Path = '"YELLOW" %d"BLUE"'\n"RESET, com->redirect->type);
				ft_printf(MAGENTA"\t------------------\n"RESET);
				red = red->next;
			}
		}
		ft_printf(CYAN"------------------\n"RESET);
		com = com->next;
		ft_printf("com->next address %p\n", com);
	}	
}

int	parser(t_ms *ms)
{
	t_tokl	*start;
	t_tokl	*end;

	start = ms->token_list;
	while (start->type != END)
	{
		end = find_end(start); 
		ft_printf("start = %s\n", start->str[0] == '\0' ? "NULLx" : start->str);
		ft_printf("end = %s\n", end->str[0] == '\0' ? "NULLx" : end->str);
		// Ok
		if (make_comnd_node(ms, start, end) != 0)
			return (1);
		start = end;
		if (start->type == PIPE)
			start = start->next;
	}
	// clean spaces
	debug_parser(ms);
	lexer_clean(ms);
	return (0);
}
