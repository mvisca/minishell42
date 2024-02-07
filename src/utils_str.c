#include "../include/minishell.h"

int utils_skip_spaces(char *str, int i)
{
    while (str && str[i] && ft_isspace(str[i]))
        i++;
    return (i);
}