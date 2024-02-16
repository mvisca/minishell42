/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:40:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/16 05:53:19 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lexer_clean(t_minishell *ms)
{
	t_tokenlst	*aux;
	t_tokenlst	*next;

	aux = ms->token_list;
	ms->token_list = NULL;
	while (aux)
	{
		next = aux->next;
		free(aux->str);
		aux->str = NULL;
		free(aux);
		aux = next;
	}
	ft_printf("Desde lexer_tolls.c\nSe limpió ms->token_list\n");
	return (ft_printf("linea estará parseada en ms->comnd_list\n"));
}
