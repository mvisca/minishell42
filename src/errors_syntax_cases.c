/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:37 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/05 19:46:58 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	errors_pipe(t_ms *ms, t_tokl *token)
{
	char	*str;

	if ((ft_strchr(ms->line, '|') + 1)[0] == '|')
		str = ft_strdup("||");
	else
		str = ft_strdup("|");
	if (token->type == token->next->type)
	{
		errors_syntax_display(ms, str);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	errors_redir(t_ms *ms, t_tokl *token)
{
	if (token->type == L_REDIRECT && token->next->type == L_REDIRECT)
		errors_syntax_display(ms, "<");
	else if (token->type == R_REDIRECT && token->next->type == R_REDIRECT)
		errors_syntax_display(ms, ">");
	else if (token->type == DL_REDIRECT && token->next->type == DL_REDIRECT)
		errors_syntax_display(ms, "<<");
	else if (token->type == DR_REDIRECT && token->next->type == DR_REDIRECT)
		errors_syntax_display(ms, ">>");
	else
		return (0);
	return (1);
}

int	errors_word(t_ms *ms, t_tokl *tok)
{
	size_t	i;
	size_t	j;

	while (tok->type)
	{
		i = 0;
		while (tok->str[i])
		{
			if (tok->str[i] == D_QUOTE || tok->str[i] == S_QUOTE)
			{
				j = i;
				str_close_quote(tok->str, &i);
				if (tok->str[j] != tok->str[i])
					return (errors_syntax_display(ms, "Open Quotes"));
			}
			i++;
		}
		tok = tok->next;
	}
	return (0);
}

int	errors_start(t_ms *ms)
{
	t_tokl	*tok;
	t_tokl	*prev;

	tok = ms->token_list;
	if (tok->type == PIPE)
		return (errors_syntax_display(ms, "|"));
	while (tok->type)
	{
		prev = tok;
		tok = tok->next;
	}
	if (prev->type == PIPE)
		errors_syntax_display(ms, "|");
	return (0);
}
