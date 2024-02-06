#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_envlst
{
	char				*key;
	char				*value;
	struct s_envlst		*next;
}	t_envlst;

typedef struct s_tokenlst
{
	char				*str;
	int					type;
	struct s_tokenlst	*next;
}	t_tokenlst;

typedef struct s_comndlst
{
	char				*command;
	char				*redirect;
	struct s_comndlst	*next;
}	t_comndlst;

typedef struct s_minishell
{
	char				*line;
	t_tokenlst			*token_list;
	t_comndlst			*comnd_list;
	char				**envarr;
	t_envlst			*envlst;
	int					init_fd[2];
	int					curr_fd[2];
	int					prev_fd[2];
	int					status;
}	t_minishell;

#endif
