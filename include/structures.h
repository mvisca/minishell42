#ifndef STRUCTURES_H
# define STRUCTURES_H

// Copia lo key value de env
typedef struct s_envl
{
	char				*key;
	char				*value;
	struct s_envl		*next;
}	t_envl;

// Nodo de lista de tokens
typedef struct s_tokl
{
	int					type;
	char				*str;
	struct s_tokl		*next;
}	t_tokl;

// Nodo de lista de redirects anidado en commandos
typedef struct s_redl
{
	int					type;
	char				*path;
	struct s_redl		*next;
} t_redl;

// Nodo de lista de comandos
typedef struct s_coml
{
	t_tokl				*pre_cmnd;
	t_tokl				*pre_redir;
	char				**command;
	t_redl				*redirect;
	struct s_coml		*next;
}	t_coml;

// Estructura macro
typedef struct s_ms
{
	char				*line;
	t_tokl				*token_list;
	t_coml				*cmnd_list;
	t_coml				*comnd_list_fake;
	char				**envarr;
	t_envl				*envlst;
	int					init_fd[2];
	int					curr_fd[2];
	int					prev_fd[2];
	int					exit_code;
}	t_ms;

// Reune las variables de la de función extract en parser
typedef struct	s_ints
{
	int		sq;
	int		dq;
	int		i;
	int		ini;
	size_t	len;
	t_tokl	*pre_cmnd;
	t_tokl	*pre_redir;
}	t_ints;

#endif
