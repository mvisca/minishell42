/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/17 20:41:48 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser(t_ms *ms)
{
	t_tokl	*start;
	t_tokl	*end;

	start = ms->token_list;
	while (start->type != END)
	{
		end = find_end(start);
		if (make_comnd_node(ms, start, end) != 0)
			return (1);
		start = end;
		if (start->type == PIPE)
			start = start->next;
	}
	// clean spaces
	lexer_clean(ms);
	return (0);
}
