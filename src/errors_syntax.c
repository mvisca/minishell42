#include "../include/minishell.h"

static int	errors_syntax_found(t_minishell *ms, int msj)
{
	ft_printf("minishell: syntax error, macro value = %d\n", msj);
	ms->exit_code = 2;
	return (ms->exit_code);
}

static int	errors_syntax2(char *line)
{
	if (!ft_strncmp(line, "@@@", 3))
		return (SYNTAX_FAKE_ARROBA_X3);
	return (0);
}

int	errors_syntax(t_minishell *ms)
{
	int i;

	i = 0;
	if (!ft_strncmp(&ms->line[i], "|", 1))
		return (errors_syntax_found(ms, SYNTAX_PIPE_AT_0));
		// minishell: syntax error near unexpected token `|'
	while (ms->line[i])
	{
		if (!ft_strncmp(&ms->line[i], "<<<", 3))
			return (errors_syntax_found(ms, SYNTAX_BACK_RD_X3));
			// minishell: syntax error near unexpected token `newline'
		else if (!ft_strncmp(&ms->line[i], ">>>", 3))
			return (errors_syntax_found(ms, SYNTAX_FOWARD_RD_X3));
		// minishell: syntax error near unexpected token `>'
		else if (!ft_strncmp(&ms->line[i], "|||", 3))
			return (errors_syntax_found(ms, SYNTAX_FOWARD_RD_X3));
		// minishell: syntax error near unexpected token `|'
		else if (errors_syntax2(&ms->line[i]))
			return (errors_syntax_found(ms, errors_syntax2(&ms->line[i])));
		i++;
	}
	ft_printf("Received (delimited with '<' and '>'): <\x1b[31m%s\x1b[0m>\n", ms->line);
	ft_printf("No syntax error found, add new cases\n");
	return (0);
}