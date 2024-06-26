/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca-g <mvisca-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 05:10:25 by mvisca            #+#    #+#             */
/*   Updated: 2024/04/19 08:26:31 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Fix information lose when env var value includes the char '='
static int	check_oversplit(t_envl *new, char **pair)
{
	char	*aux;
	int		i;

	if (ft_tablen(pair) <= 2)
		return (1);
	if (pair && ft_tablen(pair) > 2)
	{
		i = 2;
		while (pair && pair[i])
		{
			aux = new->value;
			new->value = ft_strjoin(aux, "=");
			free(aux);
			aux = new->value;
			new->value = ft_strjoin(aux, pair[i]);
			free(aux);
			i++;
		}
	}
	return (0);
}

static void	environment_noenv(t_ms *ms)
{
	t_envl	*new_env;

	new_env = environment_new_node(ms, "PATH", AUTOENV);
	environment_add_node(ms, new_env);
}

// Tested Ok
t_envl	*environment_init(t_ms *ms, char **envp)
{
	int		i;
	char	**pair;
	t_envl	*new;

	i = 0;
	ms->envlst = NULL;
	while (envp && envp[i])
	{
		pair = ft_split(envp[i], '=');
		if (!pair)
			error_free_exit("malloc error", ms);
		new = environment_new_node(ms, pair[0], pair[1]);
		if (!new)
			error_free_exit("malloc error", ms);
		check_oversplit(new, pair);
		environment_add_node(ms, new);
		utils_free_tab(&pair);
		i++;
	}
	if (!envp || !environment_get_node(ms, "PATH"))
		environment_noenv(ms);
	return (ms->envlst);
}
