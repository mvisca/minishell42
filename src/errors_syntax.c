/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:52:06 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/27 20:45:51 by mvisca           ###   ########.fr       */
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

// estudiar cómo realizar esto con errno
int	errors_syntax(t_ms *ms)
{
	t_tokl	*token;

	token = ms->token_list;
	if (errors_start(ms))
		return (1);
	while (token && token->type != END)
	{
		if (token->type == PIPE && errors_pipe(ms, token))
			return (1);
		else if (token->type == WORD && errors_word(ms, token))
			return (1);
		else if (token->type != END && errors_redir(ms, token))
			return (1);
		token = token->next;
	}
	return (0);
}
