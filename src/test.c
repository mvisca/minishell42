#include "../include/minishell.h"

int main(void)
{
    char *str = "Hola esta es una string\n";
    char **tab = ft_split(str, 32);
    int i = -1;
    while (tab[++i])
        ft_printf("tab[%d] = %s\n", i, tab[i]);
    return (0);
}