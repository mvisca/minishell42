/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:10 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/21 15:17:22 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// actualiza el nivel de shell
static void	init_shell_level(t_ms *ms)
{
	int		i_lvl;
	char	*a_lvl;

	a_lvl = environment_get_value(ms, "SHLVL");
	i_lvl = ft_atoi(a_lvl);
	a_lvl = ft_itoa(i_lvl + 1);
	environment_update_node(ms, "SHLVL", a_lvl);
} 

// Sets t_ms initial values and calls enviroment initializer
// Tested Ok - Validar con las nuevas estructuras (ver con Marta)
void	initialize(t_ms *ms, int ac, char **av, char **envp)
{
//	if (ac > 1 || av[1])
//		error_exit("Este programa no admite argumentos\n", ms);
	(void)ac;//afegit
	(void)av;//afegit
	g_exit = 0;//afegit 0 com a exit_sucess
	ms->line = NULL;
	ms->token_list = NULL;
	ms->cmnd_list = NULL;
	if (!envp)
		error_exit("Variable no encontrada: no se recibió evnp\n", ms);
	ms->envlst = environment_init(ms, envp);
	init_shell_level(ms);
	ms->envarr = NULL;
	ms->strs.aux = NULL;
	ms->strs.buf = NULL;
	ms->strs.new = NULL;
	ms->init_fd[FD_IN] = dup(STDIN_FILENO);
	ms->init_fd[FD_OUT] = dup(STDOUT_FILENO);
	ms->std_in= dup(STDIN_FILENO);
	ms->std_out = dup(STDOUT_FILENO);
	ms->exit_code = 0;
	rl_initialize();
}
