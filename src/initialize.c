/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 04:50:10 by mvisca            #+#    #+#             */
/*   Updated: 2024/07/05 20:10:53 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	init_normalize_shlvl(t_ms *ms, int i_lvl, char *a_lvl)
{
	t_envl	*node;

	if (i_lvl > 999)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(a_lvl, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		node = environment_get_node(ms, "SHLVL");
		free(node->value);
		node->value = ft_strdup("1");
		return (1);
	}
	else if (i_lvl < 0)
	{
		node = environment_get_node(ms, "SHLVL");
		free(node->value);
		node->value = ft_strdup("0");
		return (1);
	}
	return (0);
}

// actualiza el nivel de shell
static void	init_shell_level(t_ms *ms)
{
	int		i_lvl;
	char	*a_lvl;

	a_lvl = environment_get_value(ms, "SHLVL");
	i_lvl = ft_atoi(a_lvl) + 1;
	if (!init_normalize_shlvl(ms, i_lvl, a_lvl))
	{
		a_lvl = ft_itoa(i_lvl);
		environment_update_node(ms, "SHLVL", a_lvl);
	}
}

void	initialize(t_ms *ms, int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_exit = 0;
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
	ms->std_in = dup(STDIN_FILENO);
	ms->std_out = dup(STDOUT_FILENO);
	ms->exit_code = 0;
	ms->syntax_errors = 0;
}
