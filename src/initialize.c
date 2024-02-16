/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:10 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/16 04:50:11 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Sets t_minishell initial values and calls enviroment initializer
// Tested Ok - Validar con las nuevas estructuras (ver con Marta)
void	initialize(t_minishell *ms, int ac, char **av, char **envp)
{
	if (ac > 1 || av[1])
		error_exit("este programa no admite argumentos\n", ms);
	ms->line = NULL;
	ms->token_list = NULL;
	ms->comnd_list = NULL;
	if (!envp)
		error_exit("variable no encontrada: no se recibió evnp\n", ms);
	ms->envlst = NULL;
	ms->envarr = envp;
	ms->envlst = environment_init(ms);
	ms->envarr = NULL;
	ms->init_fd[FD_IN] = dup(STDIN_FILENO);
	ms->init_fd[FD_OUT] = dup(STDOUT_FILENO);
	rl_initialize();
}
