#include "../include/minishell.h"

void    debug_token(t_ms *ms)
{
    t_tokl  *token;
    int     i;

    ft_printf("debug token\n");
    token = ms->token_list;
    i = 1;
    while (token)
    {
        ft_printf("token %d\n", i);
        ft_printf("token -> str -> '%s'\n", token->str);
        ft_printf("token -> type -> %d\n", token->type);
        ft_printf(RED"--------------\n"RESET);
        token = token->next;
        i++;
    }
}