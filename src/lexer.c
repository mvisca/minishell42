#include "../include/minishell.h"

static t_tokenlst	*add_token(t_minishell *ms, t_tokenlst *token)
{
	t_tokenlst	*aux;

	if (!ms->token_list)
		ms->token_list = token;
	else
	{
		aux = ms->token_list;
		while (aux->next)
			aux = aux->next;
		aux->next = token;
	}
	return (ms->token_list);
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
	if (type == L_REDIRECT)
		token->str = ft_strdup("<");
	if (type == R_REDIRECT)
		token->str = ft_strdup(">");
	if (type == DL_REDIRECT)
		token->str = ft_strdup(">>");
	if (type == DR_REDIRECT)
		token->str = ft_strdup("<<");
	if (type == END)
		token->str = NULL;
	if (type == WORD)
		token->str = make_token_word(line);
	if (!token->str)
		return (ft_strlen(ms->line + 1));
	add_token(ms, token);
	return ((int)ft_strlen(token->str));
}

// static void	debug_print_lexer(t_minishell *ms)
// {
	// TESTEAR LEXER IMPRIMIENDO MS->TOKEN_LIST
	// MIENTRAS HAYA NODO
	// IMPRIMO EL NODO
	// NODO AUX IGUAL AL SIGUIENTE...
// }

int lexer(t_minishell *ms, char *l)
{
	int		i;
	
	i = 0;
	while (i <= (int)ft_strlen(l) && l && l[i])
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
		else if (l[i] == '\0')
			i += make_token(ms, &l[i], END);
		else
			i += make_token(ms, &l[i], WORD);
	}
	if (i > (int)ft_strlen(l))
		return (1);
	return (0);		
}
