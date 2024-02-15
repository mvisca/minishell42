#include "../include/minishell.h"

void	debug_lexerlst(t_minishell *ms)
{
	t_tokenlst	*aux;
	int			i;

	i = 1;
	aux = ms->token_list;
	while (aux)
	{
		ft_printf(YELLOW"token %d\n"RESET, i++);
		ft_printf("\ttoken -> str = '%s'\n", aux->str);
		ft_printf("\ttoken -> type = %d\n", aux->type);
		ft_printf("----------------\n");
		aux = aux->next;
	}
	ft_printf(YELLOW"LAST"RED" token %d\n"RESET, i++);
	ft_printf("\ttoken -> str = '%s'\n", aux->str);
	ft_printf("\ttoken -> type = %d\n", aux->type);
	ft_printf("----------------\n");
}

void    lexer_clean(t_minishell *ms)
{
    t_tokenlst  *aux;
    t_tokenlst  *next;

    aux = ms->token_list;
	ms->token_list = NULL;
    while (aux)
    {
		// ft_printf("lexer_clean pre address = %p\n", ms->token_list);
		
		// ft_printf("lexer_clean pre address of aux->str = %p\n", aux->str);

        next = aux->next;
        free(aux->str);
		aux->str = NULL;
		
		// ft_printf("lexer_clean post address of aux->str = %p\n", aux->str);
		

		// ft_printf("lexer_clean post address = %p\n", aux->next);
        
		free(aux);
		aux = next;
    }
	ft_printf("Se limpió ms->token_list\n");
}
