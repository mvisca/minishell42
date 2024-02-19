/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:56:59 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/19 20:38:30 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	populate_comnd_node(t_ms *ms, t_tokl **start)
{

	while ((*start)->type != PIPE && (*start)->type != END)
	{
		if ((*start)->type == WORD)
		{
			array_append(ms->comnd_list, *start);
			*start = (*start)->next;
		}
		else
		{
			ms->comnd_list->redirect = make_redir_node(ms->comnd_list); // que pasa aqui
			if (!ms->comnd_list->redirect)
				return (1);
			ms->comnd_list->redirect->type = (*start)->type;
			*start = (*start)->next;
			if ((*start)->type != WORD)
				ms->comnd_list->redirect->path = NULL;
			else
				ms->comnd_list->redirect->path = ft_strdup((*start)->str);
		}
		if ((*start)->type != END)
			*start = (*start)->next;			
	}
	return (0);	
}
	
	// si es typo word = (*start)->
		// lo mete en array
		// itera el nodo
	// si es != word y != end
		// crea puebla el nodo de redirect
		// crea otro nodo en la lista 
			// puedo dejar el nodo vacío y no crear nada
			// pero da igual
		// itera el nodo hasta el PIPE o el END
