#include "../include/minishell.h"

void    debug_token(t_ms *ms)
{
    t_tokl  *token;
    int     i;

	ft_printf(YELLOW"- - - - - - - - - - -\n"RESET);
	ft_printf(RED"LEXER"RESET""BLUE" -> "RESET"debug start\n");

    token = ms->token_list;
    i = 1;
    while (token)
    {
        ft_printf("token %d \t| str -> "BLUE"%s"RESET"\t\t| type -> %d\n", i, token->str, token->type);
        ft_printf(RED"----------------------------------------------------\n"RESET);
        token = token->next;
        i++;
    }
	ft_printf(RED"LEXER"RESET""BLUE" -> "RESET"debug done\n");
	ft_printf(BLUE"- - - - - - - - - -\n"RESET);
}

void	debug_command(t_ms *ms)
{
	t_coml	*cmnd_aux;
	t_redl	*redir_aux;
	int		i;
	int		count;

	ft_printf(GREEN"- - - - - - - - - - -\n"RESET);
	ft_printf(GREEN"PARSER"RESET""BLUE" -> "RESET"debug start\n");
	cmnd_aux = ms->cmnd_list;
	count = 1;
	while (cmnd_aux)
	{
		ft_printf(BLUE"Cmnd node"YELLOW" Nº %d\n"RESET, count);
		i = -1;
		while (cmnd_aux->command && cmnd_aux->command[++i])
		{
			ft_printf("\tcmnd->command[%d] address = %p\n", i, cmnd_aux->command[i]);
			ft_printf("\tcmnd->command[%d] = %s\n", i, cmnd_aux->command[i]);
		}
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
	ft_printf(GREEN"PARSER"RESET""BLUE" -> "RESET"debug done\n");
	ft_printf(GREEN"- - - - - - - - - -\n"RESET);
}

void	debug_envarr(t_ms *ms)
{
	int i;

	ft_printf(YELLOW"- - - - - - - - - -\n"RESET);
	ft_printf(RED"ENVIRONMENT"RESET" <envarr> "BLUE" -> "RESET"debug start\n");
	i = 0;
	while (ms->envarr && ms->envarr[i])
	{
		if (ft_strnstr(ms->envarr[i], "PATH", 4))
			ft_printf(RED"envarr[%d] >"BLUE" %s\n"RESET, i, ms->envarr[i]);
		else if (ft_strnstr(ms->envarr[i], "SHLVL", 5))
			ft_printf(RED"envarr[%d] >"YELLOW" %s\n"RESET, i, ms->envarr[i]);
		else 
			ft_printf(RED"envarr[%d] >"RESET" %s\n", i, ms->envarr[i]);
		i++;
	}
	ft_printf(RED"ENVIRONMENT"RESET" <envarr> "BLUE" -> "RESET"debug done\n");
	ft_printf(GREEN"- - - - - - - - - -\n"RESET);
}

void	debug_tab(char **tab)
{
	int i;

	ft_printf(YELLOW"- - - - - - - - - -\n"RESET);
	ft_printf(RED"TAB -> "RESET"debug start\n");
	i = 0;
	while (tab && tab[i])
	{
		if (ft_strnstr(tab[i], "PATH", 4))
			ft_printf(RED"TAB[%d] >"BLUE" %s\n"RESET, i, tab[i]);
		else if (ft_strnstr(tab[i], "SHLVL", 5))
			ft_printf(RED"TAB[%d] >"YELLOW" %s\n"RESET, i, tab[i]);
		else 
			ft_printf(RED"TAB[%d] >"RESET" %s\n", i, tab[i]);
		i++;
	}
	ft_printf(RED"TAB"RESET" <TAB> "BLUE" -> "RESET"debug done\n");
	ft_printf(GREEN"- - - - - - - - - -\n"RESET);
}

int	debug_all(t_ms *ms, int env, int tok, int com)
{
	if (env)
		debug_envarr(ms);
	if (tok)
		debug_token(ms);
	if (com)
		debug_command(ms);
	return (1);
}
