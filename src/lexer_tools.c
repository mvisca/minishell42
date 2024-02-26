/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:40:29 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/26 19:52:52 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tokl	*lexer_add_token(t_ms *ms, t_tokl *token)
{
	t_tokl	*aux;

	aux = ms->token_list;
	if (!aux)
		ms->token_list = token;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = token;
	}
	return (aux);
}

char	*lexer_make_token_word(char *line)
{
	int		i;
	char	*word;
	char	*trim_word;

	i = 0;
	while (line[i] && line[i] != '|' && line[i] != '>' && line[i] != '<')
		i++;
	word = ft_substr(line, 0, i);
	trim_word = ft_strtrim(word, SPACES);
	free(word);
	return (trim_word);
}

int	lexer_end_token(t_ms *ms)
{
	t_tokl	*token;

	token = (t_tokl *)malloc(sizeof(t_tokl));
	if (!token)
		return (1);
	token->next = NULL;
	token->str = NULL;
	token->type = END;
	lexer_add_token(ms, token);
	return (0);
}

int	lexer_make_token(t_ms *ms, char *line, int type)
{
	t_tokl	*token;

	token = (t_tokl *)malloc(sizeof(t_tokl));
	if (!token)
		return (ft_strlen(ms->line));
	if (type == PIPE)
		token->str = ft_strdup("|");
	else if (type == L_REDIRECT)
		token->str = ft_strdup("<");
	else if (type == R_REDIRECT)
		token->str = ft_strdup(">");
	else if (type == DL_REDIRECT)
		token->str = ft_strdup("<<");
	else if (type == DR_REDIRECT)
		token->str = ft_strdup(">>");
	else
		token->str = lexer_make_token_word(line);
	token->type = type;
	token->next = NULL;
	lexer_add_token(ms, token);
	return ((int)ft_strlen(token->str) || 1);
}

void	lexer_skip_empty_token(t_ms *ms)
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
