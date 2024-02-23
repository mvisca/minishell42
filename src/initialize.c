/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:10 by mvisca            #+#    #+#             */
/*   Updated: 2024/02/23 08:14:32 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// init temporal para deasrrollar executor mientras completo el parser
static t_comndlst	*make_command(t_minishell *ms)
{
	ms->comnd_list_fake = (t_comndlst *) malloc (sizeof(t_comndlst));
	ms->comnd_list_fake->command = (char **) malloc (sizeof(char *) * 2);
	ms->comnd_list_fake->command[0] = ft_strdup("ls");
	ms->comnd_list_fake->command[1] = NULL;
	ms->comnd_list_fake->redirect = NULL;
	ms->comnd_list_fake->next = (t_comndlst *) malloc (sizeof(t_comndlst));
	ms->comnd_list_fake->next->command = (char **) malloc (sizeof(char *) * 3);
	ms->comnd_list_fake->next->command[0] = ft_strdup("grep");
	ms->comnd_list_fake->next->command[1] = ft_strdup("file");
	ms->comnd_list_fake->next->command[2] = NULL;
	ms->comnd_list_fake->next->redirect = (t_redirlst *) malloc (sizeof(t_redirlst));
	ms->comnd_list_fake->next->redirect->type = R_REDIRECT;
	ms->comnd_list_fake->next->redirect->path = ft_strdup("filex.txt");
	ms->comnd_list_fake->next->redirect->next = NULL;
	ms->comnd_list_fake->next->next = NULL;
	return (ms->comnd_list_fake);
}

// Sets t_minishell initial values and calls enviroment initializer
// Tested Ok - Validar con las nuevas estructuras (ver con Marta)
void	initialize(t_minishell *ms, int ac, char **av, char **envp)
{
	if (ac > 1 || av[1])
		error_exit("este programa no admite argumentos\n", ms);
	ms->line = NULL;
	ms->token_list = NULL;
	ms->comnd_list = NULL;
	ms->comnd_list_fake = make_command(ms); // para desarrollar executor
	if (!envp)
		error_exit("variable no encontrada: no se recibió evnp\n", ms);
	ms->envlst = environment_init(ms, envp);
	ms->envarr = NULL;
	ms->init_fd[FD_IN] = dup(STDIN_FILENO);
	ms->init_fd[FD_OUT] = dup(STDOUT_FILENO);
	rl_initialize();
}
