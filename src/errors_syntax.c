/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:52:06 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/21 07:32:40 by fcatala-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	errors_syntax_display(t_ms *ms, char *str)
{
	ft_putstr_fd(SYNTAX_MSSG, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd("\n", 2);
	ms->exit_code = 2;
	return (1);
}

int	errors_syntax(t_ms *ms)
{
	t_tokl	*token;
	t_tokl	*prev;

	if (errors_start(ms))
		return (1);
	token = ms->token_list;
	prev = NULL;
	while (token && token->type != END)
	{
		if (token->type == WORD && errors_word(ms, token))
			return (1);
		if (token->type != END && errors_redir(ms, token))
			return (1);
		if (token->type == PIPE && token->next->type == END)
		{
			if (prev && prev->type == PIPE && errors_pipe(ms, prev))
				return (1);
			errors_syntax_display(ms, "|");
			return (1);
		}
		prev = token;
		token = token->next;
	}
	return (0);
}
