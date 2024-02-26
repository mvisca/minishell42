/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:40:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 21:54:38 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



char	*make_token_word(char *line)
{
	int		i;
	char	*word;

	i = 0;
	while (line[i] && line[i] != '|' && line[i] != '>' && line[i] != '<')
		i++;
	word = ft_substr(line, 0, i);
	return (word);
}



void	skip_empty_token(t_ms *ms)
{
	t_tokl	*token;
	t_tokl	*next;
	
	token = ms->token_list;
	while (token->next)
	{
		if (token->next->type == 9 && !str_only_spaces(token->next->str))
		{
			next = token->next;
			token->next = token->next->next;
			free(next->str);
			free(next);
		}
		else
			token = token->next;
	}
}
