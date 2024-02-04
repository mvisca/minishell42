#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_envlst
{
	char			*key;
	char			*value;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	char		*str;
	int			str_type;
}	t_parse;

typedef struct s_minishell
{
	char		*line;
	t_token		*lex;
	t_parse		*tokens;
	int			tokens_count;
	char		**envp;
	t_envlst	*envlst;
	int			init_fd[2];
	int			curr_fd[2];
	int			prev_fd[2];
	int			status;
}	t_minishell;

#endif
