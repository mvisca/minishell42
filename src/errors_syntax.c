/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:52:06 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/16 06:17:58 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	errors_get_string(int error_code)
{
	char	c;

	if (error_code == SYNTAX_PIPE_AT_0 || error_code == SYNTAX_PIPE_X3)
		c = '|';
	else if (error_code == SYNTAX_BACK_RD_X3)
		c = '<';
	else if (error_code == SYNTAX_FOWARD_RD_X3)
		c = '>';
	else if (error_code == SYNTAX_FAKE_ARROBA_X3)
		c = '@';
	else if (error_code == SYNTAX_CURLY_START)
		c = '{';
	else if (error_code == SYNTAX_CURLY_END)
		c = '}';
	else
		c = '?';
	return (c);
}

static int	errors_syntax_display(t_minishell *ms, int error_code)
{
	char	c;

	c = errors_get_string(error_code);
	ft_printf("%s%c'\n", SYNTAX_MSSG, c);
	ms->exit_code = 2;
	return (0);
}

static int	errors_syntax_found2(char *line)
{
	int	error_code;

	error_code = 0;
	if (!ft_strncmp(line, "@@@", 3))
		error_code = SYNTAX_FAKE_ARROBA_X3;
	return (error_code);
}
//	else if (....)
//		error_code = ....;
//	else
//		errors_syntax_found3(.....);

static int	errors_syntax_found(t_minishell *ms, int i)
{
	int		error_code;
	char	*line;

	error_code = 0;
	line = &ms->line[i];
	if (i == 0 && !ft_strncmp(&ms->line[i], "|", 1))
		error_code = SYNTAX_PIPE_AT_0;
	else if (!ft_strncmp(line, "|||", 3))
		error_code = SYNTAX_PIPE_X3;
	else if (!ft_strncmp(line, "<<<", 3))
		error_code = SYNTAX_BACK_RD_X3;
	else if (!ft_strncmp(line, ">>>", 3))
		error_code = SYNTAX_FOWARD_RD_X3;
	else if (!ft_strncmp(line, "{", 1))
		error_code = errors_syntax_curly_brackets(line);
	else if (!ft_strncmp(line, "}", 1))
		error_code = SYNTAX_CURLY_END;
	else
		error_code = errors_syntax_found2(&ms->line[i]);
	return (error_code);
}

// estudiar cómo realizar esto con errno
int	errors_syntax(t_minishell *ms)
{
	int	error_code;
	int	i;

	error_code = 0;
	i = 0;
	while (ms->line[i])
	{
		error_code = errors_syntax_found(ms, i);
		if (error_code)
			break ;
		i++;
	}
	if (error_code)
		errors_syntax_display(ms, error_code);
	return (error_code);
}
