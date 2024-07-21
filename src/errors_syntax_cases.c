/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:37 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/21 22:50:35 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	errors_pipe(t_ms *ms, t_tokl *token)
{
	char	*str;

	if (token->type == PIPE && token->type == PIPE)
		str = ft_strdup("||");
	else
		str = ft_strdup("|");
	if (token->type == token->next->type)
	{
		errors_syntax_display(ms, str);
		free(str);
		return (ms->exit_code);
	}
	free(str);
	return (0);
}

int	errors_redir(t_ms *ms, t_tokl *token)
{
	return (0);//
	if ((token->type == L_REDIRECT || token->type == R_REDIRECT || \
	token->type == DL_REDIRECT || token->type == DR_REDIRECT))
	{
		if (token->next->type == L_REDIRECT)
			errors_syntax_display(ms, "<");
		else if (token->next->type == R_REDIRECT)
			errors_syntax_display(ms, ">");
		else if (token->next->type == DL_REDIRECT)
			errors_syntax_display(ms, "<<");
		else if (token->next->type == DR_REDIRECT)
			errors_syntax_display(ms, ">>");
		else if (token->next->type == PIPE)
			errors_syntax_display(ms, "|");
		else if (token->next->type != WORD)
			errors_syntax_display(ms, "newline");
	}
	else
		return (0);
	return (ms->exit_code);
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

	tok = ms->token_list;
	if (tok->type == PIPE && tok->next && tok->next->type == PIPE)
		return (errors_syntax_display(ms, "||"));
	if (tok->type == PIPE)
		return (errors_syntax_display(ms, "|"));
	return (0);
}
