#include "../include/minishell.h"

int lexer(t_minishiell *ms)
{
	// tengo la línea
	// voy a buclear
		// limpiar espacios
		// lexar usando macros
	
	int		i;
	char	**line;

	line = ft_split(ms->line, ' ');
	if (!line)
		return (1); // devolver error que borra todo
	i = 0;
	while (line && line[i])
	{
		if (is_dollar(line[i]))
CONTINUAR
	}
		
}


/*
typedef struct s_tokenlst
{
	char				*str;
	int					type;
	struct s_tokenlst	*next;
}	t_tokenlst;e

END
DOLLAR
DQUOTE
SQUOTE
PIPE
REDIREC
WORD
*/