#include "../include/minishell.h"

void    debug_token(t_ms *ms)
{
    t_tokl  *token;
    int     i;

	ft_printf(YELLOW"- - - - - - - - - - -\n"RESET);
	ft_printf(RED"LEXER"RESET""BLUE" -> "RESET"debug start\n");
	ft_printf(BLUE"- - - - - - - - - - -\n"RESET);

    token = ms->token_list;
    i = 1;
    while (token)
    {
        ft_printf("token %d \t| str -> "BLUE"%s"RESET"\t\t| type -> %d\n", i, token->str, token->type);
        ft_printf(RED"----------------------------------------------------\n"RESET);
        token = token->next;
        i++;
    }
	ft_printf(YELLOW"- - - - - - - - - -\n"RESET);
	ft_printf(RED"LEXER"RESET""BLUE" -> "RESET"debug done\n");
	ft_printf(BLUE"- - - - - - - - - -\n"RESET);
}

void	debug_command(t_ms *ms)
{
	t_coml	*cmnd_aux;
	t_redl	*redir_aux;
	int		i;
	int		count;

	ft_printf(YELLOW"- - - - - - - - - - -\n"RESET);
	ft_printf(RED"PARSER"RESET""BLUE" -> "RESET"debug start\n");
	ft_printf(BLUE"- - - - - - - - - - -\n"RESET);
	cmnd_aux = ms->cmnd_list;
	count = 1;
	while (cmnd_aux)
	{
		ft_printf(BLUE"Nodo cmnd %d\n"RESET, count);
		i = -1;
		while (cmnd_aux->command && cmnd_aux->command[++i])
			ft_printf("\tcmnd->command[%d] = %s\n", i, cmnd_aux->command[i]);
		redir_aux = cmnd_aux->redirect;
		while (redir_aux)
		{
			ft_printf("\tcmnd->redir->type = %d\n", redir_aux->type);
			if (redir_aux->path)
				ft_printf("\tcmnd->redir->path = %s\n", redir_aux->path);
			else
				ft_printf("\tcmnd->redir->path = (null)\n");
			redir_aux = redir_aux->next;
		}
		count++;
		cmnd_aux = cmnd_aux->next;
	}
	ft_printf(YELLOW"- - - - - - - - - -\n"RESET);
	ft_printf(RED"PARSER"RESET""BLUE" -> "RESET"debug done\n");
	ft_printf(BLUE"- - - - - - - - - -\n"RESET);
}
