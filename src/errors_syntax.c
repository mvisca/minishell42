/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:52:06 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/19 09:21:28 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char	errors_get_string(int error_code)
// {
// 	char	c;

// 	if (error_code == SYNTAX_PIPE_AT_0 || error_code == SYNTAX_PIPE_X2)
// 		c = '|';
// 	else if (error_code == SYNTAX_BACK_RD_X3)
// 		c = '<';
// 	else if (error_code == SYNTAX_FOWARD_RD_X3)
// 		c = '>';
// 	else if (error_code == SYNTAX_FAKE_ARROBA_X3)
// 		c = '@';
// 	else if (error_code == SYNTAX_CURLY_START)
// 		c = '{';
// 	else if (error_code == SYNTAX_CURLY_END)
// 		c = '}';
// 	else
// 		c = '?';
// 	return (c);
// }

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
