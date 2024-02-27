/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:48:44 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/27 21:22:01 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lexer_make_token_str(char *line)
{
	int		i;
	char	*word;

	i = 0;
	while (line[i] && line[i] != '|' && line[i] != '>' && line[i] != '<')
		i++;
	word = ft_substr(line, 0, i);
	return (word);
}

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

int	lexer_make_token(t_ms *ms, char *line, int type, int *i)
{
	t_tokl	*new;
	size_t	len;

	new = (t_tokl *)malloc(sizeof(t_tokl));
	if (!new)
		return (1);
	new->type = type;
	new->str = NULL;
	new->next = NULL;
	if (type == WORD)
	{
		len = str_line_len(line);
		new->str = ft_substr(line, 0, len);
		(*i) += len;
	}
	else
	{
		if (line)
			new->str = ft_strdup(line);
		(*i) += ft_strlen(new->str);
	}
	lexer_add_token(ms, new);
	return (0);
}

int	lexer(t_ms *ms, char *line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
			lexer_make_token(ms, "|", PIPE, &i);
		else if (ft_strnstr(&line[i], ">>", 2))
			lexer_make_token(ms, ">>", DR_REDIRECT, &i);
		else if (ft_strnstr(&line[i], "<<", 2))
			lexer_make_token(ms, "<<", DL_REDIRECT, &i);
		else if (line[i] == '>')
			lexer_make_token(ms, ">", R_REDIRECT, &i);
		else if (line[i] == '<')
			lexer_make_token(ms, "<", L_REDIRECT, &i);
		else
			lexer_make_token(ms, &line[i], WORD, &i);
	}
	lexer_make_token(ms, NULL, END, &i);
	return (0);
}


