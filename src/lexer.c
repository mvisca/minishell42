#include "../include/minishell.h"

static t_tokenlst	*add_token(t_minishell *ms, t_tokenlst *token)
{
	t_tokenlst	*aux;

	ft_printf(BLUE"add_token"RED" AÑADIR "YELLOW"TOKEN\n"RESET);
	ft_printf("token_lst head address = %p\n", ms->token_list);

	aux = ms->token_list;
	if (!aux)
		ms->token_list = token;
	else
	{
		while (aux->next)
			aux = aux->next;
		aux->next = token;

		ft_printf("in add_token, token->str "RED"%s"RESET" token->type "RED"%d\n", token->str, token->type);

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
		return (ft_strlen(ms->line));
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
	else if (type == WORD || type == END)
		token->str = make_token_word(line);
	else
		ft_printf("Impossible outcome\n");
	token->type = type;
	token->next = NULL;
	add_token(ms, token);
	return ((int)ft_strlen(token->str));
}

int lexer(t_minishell *ms, char *l)
{
	int		i;
	
	i = 0;
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
	if (i > (int)ft_strlen(l))
	{
		ft_printf("Exit\n");
		return (lexer_clean(ms));	
	}
	free(ms->line);
	make_token(ms, "", END);
	debug_lexerlst(ms);
	return (0);		
}
