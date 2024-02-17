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

typedef struct s_redirlst
{
	int					type;
	char				*path;
	struct s_redirlst	*next;
} t_redirlst;

typedef struct s_comndlst
{
	char				**command; // command[0] = comando; command[1] = opciones... command[n] = NULL;
	t_redirlst			*redirect; // NULL o VALIDO
	struct s_comndlst	*next;
}	t_comndlst;

typedef struct s_minishell
{
	char				*line;
	t_tokenlst			*token_list;
	t_comndlst			*comnd_list;
	t_comndlst			*comnd_list_fake;
	char				**envarr;
	t_envlst			*envlst;
	int					init_fd[2];
	int					curr_fd[2];
	int					prev_fd[2];
	int					exit_code; // los forks haran exit con codigo de salida, con waitpid los recogeremos y actualizaremos la variable del struct t_minishel "exit_code" que estará disponible para la posible ejecución de comando "echo $?"
}	t_minishell;

#endif
