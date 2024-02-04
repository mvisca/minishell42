#include "../include/minishell.h"

/* void	ms_put_error(t_minishell *ms, t_tokenlst *token, char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(token->command[1], 2);
	ft_putstr_fd("\n", 2);
	errno = 127;
	ms->status = 127;
}
*/

void	ms_error_exit(char *msj, t_minishell *ms)
{
	(void)ms;
	ft_printf("%s\n", msj);
	exit (1);
}

void	ms_error_free_exit(char *msj, t_minishell *ms)
{
	ms_free_ms(ms);
	ft_printf("%s\n", msj);
	exit (1);
}
