/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvisca <mvisca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:33:01 by mvisca            #+#    #+#             */
/*   Updated: 2024/06/09 19:24:26 by mvisca-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	builtin_export_display_error(char *command)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	builtin_export_update(char *key, char *command, t_ms *ms)
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

static int	builtin_export_check_options(char *com, t_ms *ms)
{
	int		i;
	char	*key;

	ms->exit_code = 0;
	key = NULL;
	i = 0;
	if (ft_strchr("qwertyuiopasdfghjklzxcvbnm_", com[0]) || \
		ft_strchr("QWERTYUIOPASDFGHJKLZXCVBNM", com[0]))
	{
		while (ft_isalnum(com[i]))
			i++;
		key = ft_substr(com, 0, i);
		if (com[i] == '=')
			builtin_export_update(key, &com[i + 1], ms);
		else if (com[i] == '+' && com[i] == '=')
			builtin_export_update(key, &com[i + 2], ms);
		else if (!com[i])
			builtin_export_update(key, &com[i], ms);
		else
			return (builtin_export_display_error(com));
	}
	else
		builtin_export_display_error(com);
	free(key);
	return (0);
}

int	builtin_export(t_ms *ms, t_coml *cmnd)
{
	int		i;
	int		control;

	control = 0;
	i = 1;
	if (cmnd->command[i] && cmnd->command[i][0] == '\n')
		cmnd->command[i][0] = '\0';
	if (cmnd->command[i] == NULL || \
	(cmnd->command[i][0] == '\0' && !cmnd->command[i + 1]))
	{
		builtin_export_no_options(ms->envlst, ms);
		return (0);
	}
	while (!control && cmnd->command[i])
	{
		control = builtin_export_check_options(cmnd->command[i], ms);
		i++;
	}
	return (ms->exit_code);
}
