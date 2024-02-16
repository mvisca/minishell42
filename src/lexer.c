/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:48:44 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/16 06:12:31 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tokenlst	*add_token(t_minishell *ms, t_tokenlst *token)
{
	t_tokenlst	*aux;

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

int	make_token(t_minishell *ms, char *line, int type)
{
	t_tokenlst	*token;

	token = malloc(sizeof(t_tokenlst));
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
	else if (type == WORD || type == END)
		token->str = make_token_word(line);
	token->type = type;
	token->next = NULL;
	add_token(ms, token);
	return ((int)ft_strlen(token->str));
}

int	lexer(t_minishell *ms, char *l)
{
	int		i;

	i = 0;
	while (l && i <= (int)ft_strlen(l) && l[i])
	{
		if (l[i] == '|')
			i += make_token(ms, &l[i], PIPE);
		else if (ft_strnstr(&l[i], ">>", 2))
			i += make_token(ms, &l[i], DR_REDIRECT);
		else if (ft_strnstr(&l[i], "<<", 2))
			i += make_token(ms, &l[i], DL_REDIRECT);
		else if (l[i] == '>')
			i += make_token(ms, &l[i], R_REDIRECT);
		else if (l[i] == '<')
			i += make_token(ms, &l[i], L_REDIRECT);
		else
			i += make_token(ms, &l[i], WORD);
	}
	if (i > (int)ft_strlen(l))
		return (lexer_clean(ms));
	free(ms->line);
	make_token(ms, "", END);
	return (0);
}
