#include "../../include/minishell.h"

// Sets t_minishell initial values and calls enviroment initializer
// Tested Ok - Validar con las nuevas estructuras (ver con Marta)
void	ms_init(t_minishell *ms, int ac, char **av, char **envp)
{
	if (ac > 1 || av[1])
		ms_error_exit("este programa no admite argumentos\n", ms);
	ms->line = NULL;
	ms->lex = NULL;
	ms->tokens = NULL;
	if (!envp)
		ms_error_exit("variable no encontrada: no se recibió evnp\n", ms);
	ms->envp = envp;
	ms->envlst = NULL;
	ms->envlst = ms_env_init(ms);
	ms->init_fd[IN] = dup(STDIN_FILENO);
	ms->init_fd[OUT] = dup(STDOUT_FILENO);
	rl_initialize();
}
