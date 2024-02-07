#include "../include/minishell.h"

static int	curly_error_message(void)
{
	ft_printf("Unhandled '{ }' sequence.\n");
	ft_printf("Bash runs HEREDOC or has other behaviours.\n");
	ft_printf("This edge case not handled by minishell.\n");
	return (SYNTAX_CURLY_START);
}

int errors_syntax_curly_brackets(char *line)
{
	int i;

	i = 1;
	if (line[i] == '{')
		return (0);
	while (line[i])
	{
		if (!ft_strchr(&line[i], '{') || !ft_strchr(&line[i], '}'))
			return (curly_error_message());
		i++;
	}
	if (line[1] == '\0')
		return (curly_error_message());
	return (0);
}
