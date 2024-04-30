/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:52:06 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/27 18:38:23 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	errors_syntax_display(t_ms *ms, char *str)
{
	ft_printf("%s%s'\n", SYNTAX_MSSG, str);
	ms->exit_code = 2;
	return (0);
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
