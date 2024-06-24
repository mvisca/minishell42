/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:37 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/24 10:50:23 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	curly_error_message(void)
// {
// 	ft_printf("Unhandled use of '{' and/or '}'.\n");
// 	ft_printf("Bash runs HEREDOC or passes '}' as a command option.\n");
// 	ft_printf("This edge cases are not handled by minishell.\n");
// 	return (SYNTAX_CURLY_START);
// }

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

int	errors_word(t_ms *ms, t_tokl *token)
{
	if (token->type == WORD && 0)
	{
		errors_syntax_display(ms, NULL);
		return (1);
	}
	return (0);
}

int	errors_start(t_ms *ms)
{
	(void)ms;
	return (0);
}
