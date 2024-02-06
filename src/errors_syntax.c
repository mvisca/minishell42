#include "../include/minishell.h"

int    errors_syntax(t_minishell *ms)
{
    ft_printf("Received (delimited with '<' and '>'): <\x1b[31m%s\x1b[0m>\n", ms->line);
    ft_printf("Executing: syntax errors control\n");
    return (0);
}