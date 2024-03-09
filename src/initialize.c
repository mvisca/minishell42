/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:10 by mvisca            #+#    #+#             */
/*   Updated: 2024/03/09 12:52:33 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// init temporal para deasrrollar executor mientras completo el parser
static t_coml	*make_command(t_ms *ms)
{
	ms->cmnd_list_fake = (t_coml *) malloc (sizeof(t_coml));
	ms->cmnd_list_fake->command = (char **) malloc (sizeof(char *) * 2);
	ms->cmnd_list_fake->command[0] = ft_strdup("ls");
	ms->cmnd_list_fake->command[1] = NULL;
	ms->cmnd_list_fake->redirect = NULL;
	ms->cmnd_list_fake->next = (t_coml *) malloc (sizeof(t_coml));
	ms->cmnd_list_fake->next->command = (char **) malloc (sizeof(char *) * 3);
	ms->cmnd_list_fake->next->command[0] = ft_strdup("grep");
	ms->cmnd_list_fake->next->command[1] = ft_strdup("file");
	ms->cmnd_list_fake->next->command[2] = NULL;
	ms->cmnd_list_fake->next->redirect = (t_redl *) malloc (sizeof(t_redl));
	ms->cmnd_list_fake->next->redirect->type = R_REDIRECT;
	ms->cmnd_list_fake->next->redirect->path = ft_strdup("filex.txt");
	ms->cmnd_list_fake->next->redirect->next = NULL;
	ms->cmnd_list_fake->next->next = NULL;
	return (ms->cmnd_list_fake);
}

// Sets t_ms initial values and calls enviroment initializer
// Tested Ok - Validar con las nuevas estructuras (ver con Marta)
void	initialize(t_ms *ms, int ac, char **av, char **envp)
{
	int	lvl;
	
	if (ac > 1 || av[1])
		error_exit("este programa no admite argumentos\n", ms);
	ms->line = NULL;
	ms->token_list = NULL;
	ms->cmnd_list = NULL;
	ms->cmnd_list_fake = make_command(ms); // para desarrollar executor
	if (!envp)
		error_exit("variable no encontrada: no se recibió evnp\n", ms);
	// ms->envlst = NULL; // movido al environment_init
	ms->envlst = environment_init(ms, envp);
	ms->envarr = NULL;
	ms->init_fd[FD_IN] = dup(STDIN_FILENO);
	ms->init_fd[FD_OUT] = dup(STDOUT_FILENO);
	lvl = ft_atoi(environment_get_value(ms, "SHLVL")) + 1;
	environment_update_node(ms, "SHLVL", ft_itoa(lvl));
	rl_initialize();
}
