/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:46:07 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/16 09:51:23 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	make_comnd_node(t_minishell *ms, t_tokenlst *start, t_tokenlst *end)
{
	
}
// make_comnd_node()
// recibe nodos t_tokenlst
// pasa nodos a t_comndlst
// si son word los ubica en array command
// si son redir los ubica lista de redir
// cada nodo es redir o command, y el resto null

static find_end(t_tokenlst *start)
{
	t_tokenlst	*end;

	end = start;
	while (end->type != END && end->type != PIPE)
		end = end->next;
	return (end);
}

int	parser(t_minishell *ms)
{
	int			i;
	char		*aux;
	t_tokenlst	*start;
	t_tokenlst	*end;

	i = 0;
	start = ms->token_list;
	while (start->type != END)
	{ // start = make_comnd_node(ms, start); // con esto hago find_end dentro de make y actualizo start
		end = find_end(start);
		if (!make_comnd_node(ms, start, end) != 0)
			return (1);
		start = end->next;		
	} // tengo ms->comnd_list poblado con array y lista
	while (ms->comnd_list->command[i])
	{
		aux = ms->comnd_list->command[i];
		ms->comnd_list->command[i] = utils_clean_spaces(aux);
		free(aux);
		i++;
	}
	lexer_clean(ms);
	return (0);
}
