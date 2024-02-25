#include "../include/minishell.h"

void    debug_token(t_ms *ms)
{
    t_tokl  *token;
    int     i;

    ft_printf(RED"Debug Token\n"RESET);
    token = ms->token_list;
    i = 1;
    while (token)
    {
        ft_printf("token %d \t| type -> %d\t| str -> '%s'\n", i, token->type,  token->str);
        ft_printf(RED"----------------------------------------------------\n"RESET);
        token = token->next;
        i++;
    }
}

void	debug_command(t_ms *ms)
{
	int		nodo; // contar nodo
	t_coml	*com; // ms struct member command
	int		i; // iterar en command array
	t_redl	*red; // command struct member redirect

	ft_printf(RED"\nDebug Command\n\n"RESET);

	nodo = 1;
	com = ms->comnd_list;
	ft_printf("nodo inicial com address '%p' status = ", com);
	if (com)
		ft_printf(GREEN"OK\n"RESET);
	else
		ft_printf(RED"K0\n"RESET);
	
	while (com)
	{
		ft_printf(RED"nodo com number %d\n"RESET, nodo);
		i = 0;
		ms->debu.command_count = 1;
		while (com->command[i])
		{
			ft_printf(BLUE"AQUI\n");
			ft_printf(RED"com count -> %d\n"RESET, ms->debu.command_count++);
			ft_printf(RED"com -> %d\n"RESET, com->command[i++]);
		}
		red = com->redirect;
		while (red)
		{
			ft_printf(BLUE"com->command->redirect->path %s\n"RESET, red->path);
			ft_printf(BLUE"com->command->redirect->type %d\n"RESET, red->type);
			red = red->next;
		}
		nodo++;
		com = com->next;
	}
	ft_printf("Fin del command\n");
}
