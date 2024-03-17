#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_envl
{
	char				*key;
	char				*value;
	struct s_envl		*next;
}	t_envl;

typedef struct s_tokl
{
	char				*str;
	int					type;
	struct s_tokl		*next;
}	t_tokl;

typedef struct s_redl
{
	int					type;
	int					fdes;
	char				*path;
	struct s_redl		*next;
} t_redl;

typedef struct s_coml
{
	char				**command; // command[0] = comando; command[1] = opciones... command[n] = NULL;
	t_redl				*redirect; // NULL o VALIDO
	struct s_coml		*next;
}	t_coml;

typedef struct debug
{
	int	cmnd_count;
} t_deb;

typedef struct s_ms
{
	t_deb				debu;
	char				*line;
	t_tokl				*token_list;
	t_coml				*cmnd_list;
	t_coml				*cmnd_list_fake;
	char				**envarr;
	t_envl				*envlst;
	int					init_fd[2];
	int					curr_fd[2];
	int					prev_fd[2];
	int					exit_code;
}	t_ms;

#endif
