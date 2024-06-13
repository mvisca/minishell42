/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:30:37 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/13 09:13:14 by mvisca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	export_error(char *command)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	export_print_env(t_ms *ms)
{
	t_envl	*env;

	env = ms->envlst;
	// sort env
	while (env)
	{
		ft_printf("declare -x %s", env->key);
		if (env->value)
			ft_printf("=\"%s\"", env->value);
		ft_printf("\n");
		env = env->next;
	}
	ms->exit_code = 0;
	return (0);
}

int	export_update(char *key, char *command, t_ms *ms)
{
	int		i;
	t_envl	*node;

	i = 0;
	if (command[i] == '+')
	{
		i++;
		ms->strs.aux = ft_substr(&command[i], 0, ft_strlen(&command[i]));
		ms->strs.new = ft_strjoin(environment_get_value(ms, key), ms->strs.aux);
		if (!ms->strs.new)
			return (1);
		environment_update_node(ms, key, ms->strs.new);
		free(ms->strs.aux);
	}
	else
	{
		node = environment_new_node(ms, key, &command[i]);
		environment_add_node(ms, node);
	}
	ms->exit_code = 0;
	return (0);
}
