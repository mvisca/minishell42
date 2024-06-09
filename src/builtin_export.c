/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/09 15:14:29 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	builtin_export_display_error(char *command, t_ms *ms)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	ms->exit_code = 1;
	return (0);
}

static int	builtin_export_update(char *key, char *command, t_ms *ms)
{
	int		i;
	t_envl	*node;

	i = 1;
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

static int	builtin_export_no_options(t_envl *env, t_ms *ms)
{
	while (env)
	{
		ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	ms->exit_code = 0;
	return (0);
}

static int	builtin_export_check_options(char *command, t_ms *ms)
{
	int		i;
	char	*key;

	ft_printf("DAE\n");
	ms->exit_code = 0;
	key = NULL;
	i = 0;
	if (ft_strchr("qwertyuiopasdfghjklzxcvbnm_", command[0]) || \
		ft_strchr("QWERTYUIOPASDFGHJKLZXCVBNM", command[0]))
	{
		while (ft_isalnum(command[i]))
			i++;
		key = ft_substr(command, 0, i);
		if (command[i] == '=' || (command[i] == '+' && command[i + 1] == '='))
			builtin_export_update(key, &command[i + 1], ms);
		else
			builtin_export_display_error(command, ms);
	}
	else
		builtin_export_display_error(command, ms);
	free(key);
	return (0);
}

int	builtin_export(t_ms *ms, t_coml *cmnd)
{
	int		i;
	t_envl	*env;

	debug_envarr(ms);
	env = ms->envlst;
	i = 1;
	ft_printf("c0 %s\n", cmnd->command[0]);
	ft_printf("c1 %s\n", cmnd->command[1]);
	if (cmnd->command[i] == NULL)
	{
		builtin_export_no_options(env, ms);
		return (0);
	}
	while (cmnd->command[i])
	{
		ft_printf("en %d\n", i);
		builtin_export_check_options(cmnd->command[i], ms);
		i++;
	}
	return (ms->exit_code);
}
