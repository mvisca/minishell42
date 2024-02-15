#include "../include/minishell.h"

static t_tokenlst	*add_token(t_minishell *ms, t_tokenlst *token)
{
	t_tokenlst	*aux;

	ft_printf(BLUE"in add_token\n"RESET);
	ft_printf("token_lst head address = %p\n", ms->token_list);
	aux = ms->token_list;
	if (!aux)
	{
		ft_printf("in add_token, init token_list->str %s & token->type %d\n", token->str, token->type);
		ms->token_list = token;
	}
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = token;
		ft_printf("in add_token, token->str %s & token->type %d\n", token->str, token->type);
	}
	return (aux);
}

static char	*make_token_word(char *line)
{
	int		i;
	char	*word;

	i = 0;
	while (line[i] && line[i] != '|' && line[i] != '>' && line[i] != '<')
		i++;
	word = ft_substr(line, 0, i);
	return (word);
}

static int	make_token(t_minishell *ms, char *line, int type)
{
	t_tokenlst	*token;

	token = malloc(sizeof(t_tokenlst));
	if (!token)
		return (ft_strlen(ms->line + 1));
	token->type = type;
	token->next = NULL;
	if (type == PIPE)
		token->str = ft_strdup("|");
	else if (type == L_REDIRECT)
		token->str = ft_strdup("<");
	else if (type == R_REDIRECT)
		token->str = ft_strdup(">");
	else if (type == DL_REDIRECT)
		token->str = ft_strdup("<<");
	else if (type == DR_REDIRECT)
		token->str = ft_strdup(">>");
	else if (type == END)
	{
		token->str = ft_strdup("END OF USER INPUT");
		return (0);
	}
	if (type == WORD)
		token->str = make_token_word(line);
	if (!token->str)
		return (ft_strlen(ms->line + 1));
	ft_printf(BLUE"creando"YELLOW"TOKEN\n"RESET);
	ft_printf("type nodo final = "RED"%d\n"RESET, token->type);
	ft_printf("str nodo final = "RED"%s\n"RESET, token->str);
	add_token(ms, token);
	return ((int)ft_strlen(token->str));
}

int lexer(t_minishell *ms, char *l)
{
	int		i;
	
	i = 0;
	lexer_clean(ms); // será movido al final de parser() asi cuando parser tiene su trabajo hecho destruye el input que utilizó
	while (l && i <= (int)ft_strlen(l) && l[i])
	{
		if (l[i] == '|')
			i += make_token(ms, &l[i], PIPE);
		else if (ft_strnstr(&l[i], ">>", 2))
			i += make_token(ms, &l[i], DR_REDIRECT);
		else if (ft_strnstr(&l[i], "<<", 2))
			i += make_token(ms, &l[i], DL_REDIRECT);
		else if (l[i] == '>')
			i += make_token(ms, &l[i], R_REDIRECT);
		else if (l[i] == '<')
			i += make_token(ms, &l[i], L_REDIRECT);
		else
			i += make_token(ms, &l[i], WORD);
	}
 	i += make_token(ms, l, END);
	if (i > (int)ft_strlen(l))
		return (1); // crear función de control de error en malloc de t_tokenlst, que vacie la estructura e interrumpa el proceso con mensaje de error, y de inicio a un nuevo ciclo; no será neceario interrumpir la ejecución completa del programa
	debug_lexerlst(ms);
	return (0);		
}
